
#include "SunTracker.h"



inline float degToRad(float dgr)
{
  return((dgr*22)/(7*180));
}


inline uint16_t convertDayInRank(uint16_t year, uint8_t month, uint8_t day) 
{
  uint8_t daysPerMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  //Check every 4 years
  if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) 
  {
    daysPerMonth[2] = 29; //february
  }

  //Checking months and day
  if (month < 1 || month > 12 || day < 1 || day > daysPerMonth[month]) 
  {
    return -1; //Invalide date
  }


  //
  int rank = 0;
  for (int i = 1; i < month; i++) {
    rank += daysPerMonth[i];
  }
  rank += day;

  return rank;
}


SunTracker::SunTracker(CityLocalisation cityLocalisation) 
{
  this->_cityLocalisation = cityLocalisation;
}


void SunTracker::setDebug(bool debugState) 
{
  this->_debugState = debugState;
}

/*!
 * Return declination angle
 */
float SunTracker::getDeclination()
{
  
  float gamma = ((2.0*PI)/365.0)*(this->_indexOfDay-1.0);

  float declinationInRad = 0.006918 - 0.399912*cos(gamma) + 0.070257*sin(gamma)
        - 0.006758*cos(2*gamma) + 0.000907*sin(2*gamma) 
        - 0.002697*cos(3*gamma) + 0.00148*sin(3*gamma);

  if(this->_debugState)
  {
    Serial.println("Declination : "+String(declinationInRad*57.29)+" degres");
  }
  return declinationInRad*57.29;

}

/*
 * Return Equation Time
 */
float SunTracker::getEquationTime()
{
  
  float B = (2.0*PI*(this->_indexOfDay-81))/365.0;
  float equationTime = (7.53*cos(B)+1.5*sin(B)-9.87*sin(2*B));
  if(this->_debugState)
  {
    Serial.println("Equation time : "+String(equationTime));
  }
  return equationTime;
  
}

/*!
 * Return TVS 
 */
float SunTracker::getRealTime(DateTime datetime)
{

  float minute = floor(this->_cityLocalisation.longitudeDeg)*4.0;
  float seconde = floor((this->_cityLocalisation.longitudeMin))*4.0;
  float offsetTime = minute+(seconde/60.0) + this->getEquationTime();

  float tvs = datetime.hour + (datetime.minute/60.0) - this->_seasonHour + (offsetTime/60.0);
  if(this->_debugState)
  {
    Serial.println("Real Time = ="+String(tvs));
  }
  return tvs;
  
}


float SunTracker::getHourAngle(DateTime datetime)
{
  return ((datetime.hour+(datetime.minute/60.0))-12.0)*15.0;
}


float SunTracker::getElevation(DateTime datetime)
{


  float time = this->getRealTime(datetime);
  DateTime tmpDateTime = {floor(time), ((time-floor(time))*60.0)};
  float hourAngle = this->getHourAngle(tmpDateTime);


  float a = sin(degToRad(this->_declination))*sin(degToRad(this->_cityLocalisation.latitudeDeg));
  float b = cos(degToRad(this->_declination))*cos(degToRad(this->_cityLocalisation.latitudeDeg))*cos(degToRad(hourAngle));
  
  this->elevation = asin(a+b)*57.29;
  
  if(this->elevation <= 0.0)
  {
    return -1.0;
  }
  else {
    return this->elevation;
  }
  return this->elevation;
  
                    
}

float SunTracker::getAzimut(DateTime datetime)
{

  float time = this->getRealTime(datetime);
  DateTime tmpDateTime = {floor(time), ((time-floor(time))*60.0)};
  float hourAngle = this->getHourAngle(tmpDateTime);
  
  float azimut = atan(sin(degToRad(hourAngle))/(sin(degToRad(this->_cityLocalisation.latitudeDeg))*cos(degToRad(hourAngle)) - cos(degToRad(this->_cityLocalisation.latitudeDeg)) * tan(degToRad(this->_declination))));
  

  if(this->elevation<0)
  {
    return-1;
  }
  else 
  {
    if(hourAngle<0 && azimut>=0)
    {
      return (azimut*57.29)-180;
    }
    else if(hourAngle>=00 && azimut<0)
    {
      return (azimut*57.29)+180;
    }
    else
    {
      return (azimut*57.29);
    }
     
  }
  
}

void SunTracker::update(uint16_t indexOfDay, DateTime datetime)
{

  //Update 
  this->_indexOfDay = indexOfDay;

  //Update season hour
  if(indexOfDay > 303 || indexOfDay < 85)
  {
    this->_seasonHour = SeasonHour::WinterHour;
  }
  else
  {
    this->_seasonHour = SeasonHour::SummerHour;
  }

  this->_declination = this->getDeclination();
  this->elevation = this->getElevation(datetime);
  this->azimut = this->getAzimut(datetime);
  

    Serial.print("("+String(this->azimut));
    Serial.print(",");
    Serial.println(String(this->elevation)+")");
  

}

void SunTracker::debug(uint16_t rank)
{ 
  this->setDebug(false);

  Serial.println("\\addplot[mark=none, color={rgb:red,"+String(rank+rank*2)+";green,"+String(100+rank)+";blue,125}] coordinates {");
  for(float i=0.0;i<24.0;i++)
  {

    DateTime tmpDateTime = {i, 0.0};
    this->update(rank, tmpDateTime);
  }
  Serial.println("};");
  
}
