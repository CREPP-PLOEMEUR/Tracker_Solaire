/*!
  Libraries 
*/


#include "SunTracker.h"
#include "RGB.h"
#include "GNSS.h"

#include "Pinout.h"
#include "Settings.h"


//CityLocalisation city = {GPS_LATITUDE_DEG,GPS_LATITUDE_SEC, GPS_LONGITUDE_DEG, GPS_LONGITUDE_SEC};

//SunTracker sunTracker(city);


RGB led(RGB_RED_PIN,RGB_GREEN_PIN,RGB_BLUE_PIN); 

GNSS gnss(GNSS_RX, GNSS_TX, 9600);

void setup() 
{

  pinMode(13, OUTPUT);
  
  Serial.begin(9600);
  gnss.setDebugChannel(&Serial, 9600);
  gnss.setDebugState(true);

  gnss.startSelfTest();
  gnss.init();

  if(gnss.isReady())
  {
    Serial.println("<GNSS> OK");
  }
  else {
    Serial.println("<GNSS> FAIL");
  }
Serial.println("<ENDSELFTEST> FAIL");
  //DateTime tmpDateTime = {14.0, 30.0};

 //gnss.readData();
  

}

void loop() {

  gnss.readData();
  gnss.displayInformations();
  
  // put your main code here, to run repeatedly:

//gnss.simulate();
  //gnss.readData();
  delay(1000);

}
