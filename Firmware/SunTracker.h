#ifndef SUN_TRACKER_H
#define SUN_TRACKER_H

#include "Arduino.h"


typedef struct 
{
  float hour;
  float minute;
} DateTime;

typedef enum
{
  WinterHour = 1,
  SummerHour = 2
} SeasonHour;

typedef struct 
{
  uint8_t latitudeDeg;
  uint8_t latitudeMin;
  uint8_t longitudeDeg;
  uint8_t longitudeMin;

} CityLocalisation;



class SunTracker
{
  public : 

    SunTracker(CityLocalisation cityLocalisation);

    void setDebug(bool debugState);
    void update(uint16_t indexOfDay, DateTime datetime);
    void debug(uint16_t rank);


    float elevation = 0.0;
    float azimut = 0.0;
    
  private:

    CityLocalisation _cityLocalisation;

    bool _debugState = false;

    float _declination = 0.0;
    float _hourAngle = 0.0;
    uint16_t _indexOfDay = 0.0;

    SeasonHour _seasonHour = SeasonHour::WinterHour;
    

    float getDeclination();
    float getHourAngle(DateTime datetime);
    float getRealTime(DateTime datetime);
    float getEquationTime();
    float getElevation(DateTime datetime);
    float getAzimut(DateTime datetime);
    
    
    
};

#endif
