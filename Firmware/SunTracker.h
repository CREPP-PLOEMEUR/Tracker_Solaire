#ifndef SUN_TRACKER_H
#define SUN_TRACKER_H

#include "Arduino.h"

//#include "DateTime.h"
#include "GNSS_Coordinates.h"
#include "GNSS_Time.h"

/**
 * @brief 
 * 
 */

typedef enum
{
  WinterHour = 1,
  SummerHour = 2
} SeasonHour;

typedef struct 
{
  int latitudeDeg;
  int latitudeMin;
  int longitudeDeg;
  int longitudeMin;

} CityLocalisation;


/*!

*/
class SunTracker
{
  public : 

    /**
     * @brief Construct a new Sun Tracker object
     * 
     * @param cityLocalisation 
     */
    SunTracker(CityLocalisation cityLocalisation);

    void setLocalisation(GNSS_Coordinates gnss_coordinates);

    /**
     * @brief Set the Debug object
     * 
     * @param debugState : debug state (True or False)
     */
    void setDebug(bool debugState);

    /**
     * @brief Update the azimuth and elevetion of sun for a given day 
     * 
     * @param indexOfDay 
     * @param datetime 
     */
    void update(uint16_t indexOfDay, GNSS_Time gnss_time);

    void debug(uint16_t rank);


    uint16_t convertDayInRank(GNSS_Date gnss_date) ;



    float getElevation(GNSS_Time gnss_time);
    float getAzimut(GNSS_Time gnss_time);
    


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
    float getHourAngle(GNSS_Time gnss_time);
    float getRealTime(GNSS_Time gnss_time);
    float getEquationTime();

    
    
};

#endif
