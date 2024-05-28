/*!
  Libraries 
*/
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



#include "Arduino.h"

#define RED 0
#define GREEN 1
#define BLUE 2
#define CYAN 3
#define ORANGE 4
#define WHITE 5
#define PURPLE 6
#define TURQUOISE 7
#define YELLOW 8
#define MAGENTA 9
#define ROSE 10

/**
 * @brief RGB class
 * 
 */
class RGB 			
{
public:

/**
 * @brief Construct a new RGB object
 * 
 * @param pin_red 
 * @param pin_green 
 * @param pin_blue 
 */
RGB(int pin_red, int pin_green, int pin_blue);	

/**
 * @brief Power on RGB LED with color
 * 
 * @param color 
 */
void on(int color);

/**
 * @brief Blink RGB LED
 * 
 * @param color 
 * @param delai_high 
 * @param delai_low 
 * @param nombre 
 */
void blink(int color, unsigned long delai_high, unsigned long delai_low,unsigned long nombre);

/**
 * @brief Power off RGB LED
 * 
 */
void off();

/**
 * @brief Function to display random colors
 * 
 * @param delai : delay in ms 
 * @param frequence : in Hz
 */
void randomRGB(unsigned long delai, int frequence);

private:

int pin_redIN;
int pin_greenIN;
int pin_blueIN;

}; 

#include "GNSS.h"

#include "Pinout.h"
#include "Settings.h"


CityLocalisation city = {0,0, 0, 0};

SunTracker sunTracker(city);


//RGB led(RGB_RED_PIN,RGB_GREEN_PIN,RGB_BLUE_PIN); 

GNSS gnss(GNSS_RX, GNSS_TX, 9600);

void setup() 
{

  //pinMode(13, OUTPUT);
  
  /*Serial.begin(9600);
  gnss.setDebugChannel(&Serial, 9600);
  gnss.setDebugState(true);*/

  gnss.init();

  gnss.startGNSS();

  //delay(1000);

  //gnss.stopGNSS();

  //gnss.startSelfTest();
  

  if(gnss.isReady())
  {
    Serial.println("<GNSS> OK");
  }
  else {
    Serial.println("<GNSS> FAIL");
  }


}

void loop() {


  gnss.readData();


  if(gnss.isValidPosition())
  {
    
    //Serial.println("COORDINATES FOUND !");

    /*Serial.println(gnss.getCoordinates().latitude,5);
    Serial.println(gnss.getCoordinates().longitude,5);
    //Serial.println(gnss.getDate().day);
    Serial.println(String(gnss.getTime().hour)+":"+String(gnss.getTime().minute));

    sunTracker.setLocalisation(gnss.getCoordinates());
*/


    sunTracker.update(sunTracker.convertDayInRank(gnss.getDate()), {gnss.getTime().hour,gnss.getTime().minute});

    for(int a=0;a<24;a++)
    {
      Serial.println(sunTracker.getElevation({a,0}));
    }

  Serial.println("#######################");
    sunTracker.update(sunTracker.convertDayInRank({21,12,24}), {gnss.getTime().hour,gnss.getTime().minute});

    for(int a=0;a<24;a++)
    {
      Serial.println(sunTracker.getElevation({a,0}));
    }

    gnss.displayInformations();

    //Serial.println(sunTracker.getAzimut());
    //Serial.println(sunTracker.getElevation());

    
    
  }
  
  // put your main code here, to run repeatedly:

//gnss.simulate();
  //gnss.readData();
  //delay(1000);

}
