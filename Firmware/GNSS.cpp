#include "GNSS.h"

//CityLocalisation city_example = {GPS_LATITUDE_DEG,GPS_LATITUDE_SEC, GPS_LONGITUDE_DEG, GPS_LONGITUDE_SEC};


static NMEA_MessageType nmea_messageTypes[NMEA_MESSAGE_TYPE_NUMBER] = 
{
    NMEA_MessageType{"GGA"},
    NMEA_MessageType{"GLL"},
    NMEA_MessageType{"GSA"},
    NMEA_MessageType{"GSV"},
    NMEA_MessageType{"RMC"},
    NMEA_MessageType{"VTG"}
};


static NMEA_Source nmea_sources[NMEA_SOURCE_NUMBER] = 
{
    NMEA_Source{"GP", "GPS"},
    NMEA_Source{"LL", "GALILEO"},
    NMEA_Source{"GL", "GLONASS"},
    NMEA_Source{"GB", "BEIDOU"},
    NMEA_Source{"GN", "GNSS - Mix"}
};



GNSS::GNSS(GNSS_Pin_Rx rx_Pin, GNSS_Pin_Tx tx_Pin, GNSS_Baudrate gnss_baudrate) : _rx_Pin{rx_Pin}, _tx_Pin{tx_Pin}, _gnss_baudrate{gnss_baudrate}
{
    //init UART communication
    _uartDevice = new SoftwareSerial(_rx_Pin, _tx_Pin);
    _uartDevice->begin(_gnss_baudrate);

}

void GNSS::setDebugChannel(HardwareSerial *serial, uint32_t baudrate)
{
  _uartDebug = serial;
  _uartDebug->begin(baudrate);
}


void GNSS::setDebugState(GNSS_DebugState debugState) 
{
    this->_debugState = debugState;
}

void GNSS::debug(String debugData)
{
    //_uartDebug->
}


void GNSS::init(void)
{
  //_uartDevice->println("$PUBX,40,GLL,0,0,0,0*5C");
}



String GNSS::extractField(NMEA_Frame data, uint8_t indexOfData)
{
  uint8_t frameSizeData = m_nmea_parser.countOfDelimiters;//getCountDelimiters(data) - 1;

  if(indexOfData+1 > frameSizeData)
  {
    return "<ERROR>";
  }
  else
  {

    if(indexOfData == 0)
    {
      return "INDEX_DATA_NULL";
    }
    else 
    {
      uint8_t startDelimiterAddress = m_nmea_parser.indexOfDelimiters[indexOfData-1];
      uint8_t endDelimiterAddress = m_nmea_parser.indexOfDelimiters[indexOfData];

      if(1 == 5)
      {
        return "eRRRDEKDEHDE";
      }
      else 
      {
        String returnValue = "";
        for(uint8_t index = startDelimiterAddress+1; index < endDelimiterAddress; index ++)
        {
          returnValue += data[index];
        }
        return returnValue;

      }
    }
    
    

  }
}

bool GNSS::readData(void)
{


  do
  {
    //Timout

  }while(!_uartDevice->available());

  while (_uartDevice->available()) {

        char c = _uartDevice->read();

        if (c == m_nmea_settings.header) 
        {
            NMEA_Frame frame = _uartDevice->readStringUntil('\n');
            bool error = true;
            for(uint8_t i = 0; i<frame.length();i++)
            {
              if(frame[i] == m_nmea_settings.footer)
              {
                error = false;
              }
            }

            if(error == false)
            {
            this->parseString(frame);   
            _uartDebug->println(frame);     
            }
            else {
              _uartDebug->println("INVALIDE_ANSWER");
            }
   
        }
        else {

        }
    }

    return true;
}


void GNSS::displayInformations(void)
{
  _uartDebug->println("GNSS.SOURCE = "+String(m_gnss_data.source.source)+String(m_gnss_data.source.name));
  _uartDebug->println("GNSS.LATITUDE_DIR = "+String(m_gnss_data.coordinates.latitudeDirection));
  _uartDebug->println("GNSS.LONGITUDE_DIR = "+String(m_gnss_data.coordinates.LongitudeDirection));
  _uartDebug->println("GNSS.TIME = "+String(m_gnss_data.time.hour)+" h "+String(m_gnss_data.time.minute));
  _uartDebug->println("GNSS.DATE = "+String(m_gnss_data.date.day)+"/"+String(m_gnss_data.date.month)+"/"+String(m_gnss_data.date.year));
  _uartDebug->println("GNSS.SATELLITES = "+String(m_gnss_data.satellitesNumber));
  _uartDebug->println("GNSS.ALTITUDE = "+String(m_gnss_data.altitude));
}

void GNSS::parseString(NMEA_Frame data) 
{

 
  this->updateSource(data);
  this->updateMessageType(data);
  this->updateParser(data);

  

  // _uartDebug->println("TYPE="+String(m_gnss_data.messageType.name));
  if(m_gnss_data.messageType.name == nmea_messageTypes[0].name) //GGA
  {
    //Time
    _uartDebug->println("GGA");
    updateTime(this->extractField(data, 1));
    m_gnss_data.satellitesNumber = this->extractField(data, 9).toInt();
   // m_gnss_data.altitude = this->extractField(data, 8).toInt();
    //_uartDebug->println("GNSS.DATE = "+String(m_gnss_data.date.day)+"/"+String(m_gnss_data.date.month)+"/"+String(m_gnss_data.date.year));
     //m_gnss_data.time = this->getTime(this->extractField(data, 1));

 //   String nmea_latitude = this->extractField(data, 2);
//           String nmea_longitude = this->extractField(data, 3);
//           String nmea_longitude_direction = this->extractField(data, 4);
 
//           String nmea_fix = this->extractField(data, 5);
//           String nmea_count_satellite = this->extractField(data, 6);
//           String nmea_altitude = this->extractField(data, 8);
  }
  else if(m_gnss_data.messageType.name == nmea_messageTypes[1].name) //GLL
  {

  }
  else if(m_gnss_data.messageType.name == nmea_messageTypes[2].name) //GSA
  {

  }
  else if(m_gnss_data.messageType.name == nmea_messageTypes[3].name) //GSV
  {

  }
  else if(m_gnss_data.messageType.name == nmea_messageTypes[4].name) //RMC
  {
    _uartDebug->println("RMC");
    m_gnss_data.coordinates.latitudeDirection = this->extractField(data, 4)[0];
    m_gnss_data.coordinates.LongitudeDirection = this->extractField(data, 6)[0];

    //_uartDebug->println("UPDATE_DATE2");
    updateTime(this->extractField(data, 1));
    updateDate(this->extractField(data, 9));
    
    

  }

//         if(this->extractType(data) == "GGA")
//         {
//           _uartDebug->println("GGA");
//           _uartDebug->println(data);
//           //_uartDebug->println("Type : RMC");
//           //_uartDebug->println("DEDEDEDE");
//         /*  String nmea_time = this->extractField(data, 1);
//           String nmea_latitude = this->extractField(data, 2);
//           String nmea_longitude = this->extractField(data, 3);
//           String nmea_longitude_direction = this->extractField(data, 4);
 
//           String nmea_fix = this->extractField(data, 5);
//           String nmea_count_satellite = this->extractField(data, 6);
//           String nmea_altitude = this->extractField(data, 8);
//           */

//   /*        _uartDebug->println("");
//           _uartDebug->println("Time : "+String(nmea_time));
//           _uartDebug->println("Fix : "+String(nmea_fix));
//          // _uartDebug->println("latitude : "+String(nmea_latitude)+String(nmea_latitude_direction));
//           _uartDebug->println("Longitude : "+String(nmea_longitude)+String(nmea_longitude_direction));
//           _uartDebug->println("Satellites : "+String(nmea_count_satellite));
//           _uartDebug->println("Altitude : "+String(nmea_count_satellite));
//  */      
//         }
//         else if(this->extractType(data) == "GSA")
//         {
//           _uartDebug->println("GSA");
//         }
//         else if(this->extractType(data) == "GLL")
//         {
//           _uartDebug->println("GLL");
//         }
//         else if(this->extractType(data) == "VTG")
//         {
//           _uartDebug->println("FTG");
//         }
//         else if(this->extractType(data) == "RMC")
//         {
//         /*  _uartDebug->println("RMC");
//           _uartDebug->println(data);
//           //_uartDebug->println("Type : RMC");
//           //_uartDebug->println("DEDEDEDE");
//           String nmea_time = this->extractField(data, 1);
//           String nmea_warning = this->extractField(data, 2);
//           String nmea_latitude = this->extractField(data, 3);
//           String nmea_direction_latitude = this->extractField(data, 4);
//           String nmea_longitude = this->extractField(data, 5);
//           String nmea_direction_longitude = this->extractField(data, 6);

//           String nmea_date = this->extractField(data, 9);

//           _uartDebug->println("");
//           _uartDebug->println("Time : "+String(nmea_time));
//           _uartDebug->println("Mode : "+String(nmea_warning));
//           _uartDebug->println("latitude : "+String(nmea_latitude)+String(nmea_direction_latitude));
//           _uartDebug->println("Longitude : "+String(nmea_longitude)+String(nmea_direction_longitude));
//           //_uartDebug->println("Mode : "+String(nmea_mode));
//           //_uartDebug->println("DEDEDEDE");

//           uint16_t indexDay = m_sunTracker->convertDayInRank(23,12, 03);
//           //_uartDebug->println(indexDay);
//           DateTime dateTime = this->getTime(nmea_time);

//           m_sunTracker->update(indexDay, dateTime);
//           //_uartDebug->println(m_sunTracker->getAzimut());
//           //_uartDebug->println(m_sunTracker->getElevation());

        
// */

//         }
//         else if(this->extractType(data)== "GSV")
//         {
//           //_uartDebug->println("GSV");
//         }
//         else 
//         {
//           _uartDebug->println("Unknown <"+String(nmea_messageTypes[indexHeader].name));
//         }
//       }
//     }

}

void GNSS::simulate(void)
{


    digitalWrite(13, 1);
    delay(50);
    digitalWrite(13, 0);
    delay(50);
    //_uartDebug->println(NMEA_GPGGA_EXAMPLE); 
    //this->parseString(NMEA_GPGGA_EXAMPLE);   
    
    //_uartDebug->println(NMEA_GPGSV_EXAMPLE); 
    //this->parseString(NMEA_GPGSV_EXAMPLE);


    //_uartDebug->println(NMEA_GPRMC_EXAMPLE); 
   // this->parseString(NMEA_GPRMC_EXAMPLE); 
     
    //delay(1000);
}



void GNSS::updateSource(NMEA_Frame frame)
{

 //Source (STRING)
  if(m_gnss_data.source.source != "")
  {
    return ;
  }
  for(uint8_t indexSource = 0 ; indexSource < NMEA_SOURCE_NUMBER; indexSource++)
  {

    if(frame.startsWith(nmea_sources[indexSource].source))
    {
      m_gnss_data.source = nmea_sources[indexSource];
      break;
    }      
  }
}


void GNSS::clearSource()
{
  m_gnss_data.source = {"", ""};
}



void GNSS::updateMessageType(NMEA_Frame frame)
{

  m_gnss_data.messageType = this->extractType(frame) ;

}
void GNSS::clearMessageType()
{
  m_gnss_data.messageType = {""};
}






void GNSS::updateParser(NMEA_Frame data)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < data.length(); i++) {
        if (data.charAt(i) == m_nmea_settings.delimiter) 
        {
            m_nmea_parser.indexOfDelimiters[count] = i;
            count++;
        }
    }
    m_nmea_parser.countOfDelimiters = count;

}




void GNSS::updateTime(String frame)
{

  if(frame.length()<6)
  {
    return ;
  }

  m_gnss_data.time.hour = (String(char(frame[0])) + String(char(frame[1]))).toInt();
  m_gnss_data.time.minute = (String(char(frame[2])) + String(char(frame[3]))).toInt();
  m_gnss_data.time.seconde = (String(char(frame[4])) + String(char(frame[5]))).toInt();

}

void GNSS::updateDate(String frame)
{
  if(frame.length()<6)
  {
    return ;
  }
  m_gnss_data.date.day = (String(char(frame[0])) + String(char(frame[1]))).toInt();
  m_gnss_data.date.month = (String(char(frame[2])) + String(char(frame[3]))).toInt();
  m_gnss_data.date.year = (String(char(frame[4])) + String(char(frame[5]))).toInt();

}

void GNSS::startSelfTest(void)
{
 // _uartDebug->begin(baudrate);

  bool result = this->readData();
  _uartDebug->begin(">>> SELF_TEST ");

  if(result)
  {
    //_uartDebug->begin(">>> OK ");
  }
  else 
  {
   //_uartDebug->begin(">>> FAIL ");
  }

  //Extract data

  m_gnss_data.isReady = true;

  
}


bool GNSS::isReady(void)
{
  return m_gnss_data.isReady;
}


NMEA_MessageType GNSS::extractType(NMEA_Frame frame) {


    NMEA_MessageType messageType = {String(frame[2])+String(frame[3])+String(frame[4])};
   
    return messageType;
}


NMEA_Source GNSS::extractSource(NMEA_Frame chaine) {
    // Vérifier si la chaîne a au moins 5 caractères
    // if (chaine.length() < 5) {
    //     return "La chaine est trop courte";
    // }

    // // Extraire les caractères 3, 4 et 5 de la chaîne
    // NMEA_Frame caracteresExtraits = "";
    // caracteresExtraits += chaine.charAt(0); // 3ème caractère
    // caracteresExtraits += chaine.charAt(1); // 4ème caractère
    // return caracteresExtraits;
}
