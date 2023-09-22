
#include "SunTracker.h"
#include "RGB.h"

//#include <DS1302.h>

#include "Pinout.h"
#include "Settings.h"

#define DEBUG 
#define UPDATE_RTC


CityLocalisation city = {GPS_LATITUDE_DEG,GPS_LATITUDE_SEC, GPS_LONGITUDE_DEG, GPS_LONGITUDE_SEC};
DateTime currentTime = {0,0};

SunTracker sunTracker(city);
RGB led(RGB_RED_PIN,RGB_GREEN_PIN,RGB_BLUE_PIN); 
//DS1302 rtc(RTC_CS, RTC_CLK, RTC_DATA);  

void setup() 
{
  
  Serial.begin(115200);

  led.on(GREEN);
  delay(1000);
  led.off();

  #ifdef RTC_INIT
    //rtc.writeDateTime(RTC_YEAR, RTC_MONTH, RTC_DAY, RTC_HOUR, RTC_MIN, RTC_SEC);
  #endif

  DateTime tmpDateTime = {14.0, 30.0};
  
  //DateTime now = rtc.now();

    //Janvier
   /* for(int i=1;i<=31;i++)
    {
      sunTracker.debug(i);
    }
    //Fevrier
    for(int i=32;i<=62;i++)
    {
      sunTracker.debug(i);
    }*/
        //Mars
    /*for(int i=63;i<=93;i++)
    {
      sunTracker.debug(i);
    }*/
   //Avril
    for(int i=181;i<=365;i++)
    {
      sunTracker.debug(i);
    }
  //sunTracker->debug();
 // sunTracker->update(172, tmpDateTime);
  

}

void loop() {

  
  // put your main code here, to run repeatedly:

}
