/*!
  Libraries 
*/
#include "SunTracker.h"
#include "RGB.h"
#include "GNSS.h"

#include "Pinout.h"
#include "Settings.h"


CityLocalisation city = {0,0, 0, 0};

SunTracker sunTracker(city);


RGB led(RGB_RED_PIN,RGB_GREEN_PIN,RGB_BLUE_PIN); 

GNSS gnss(GNSS_RX, GNSS_TX, 9600);

void setup() 
{

  pinMode(13, OUTPUT);
  
  Serial.begin(9600);
  gnss.setDebugChannel(&Serial, 9600);
  gnss.setDebugState(true);

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


  static bool passed = false;

 // gnss.displayInformations();

  if(gnss.isValidPosition())
  {
    
    //Serial.println("COORDINATES FOUND !");
/*
    Serial.println(gnss.getCoordinates().latitude,5);
    Serial.println(gnss.getCoordinates().longitude,5);
    //Serial.println(gnss.getDate().day);
    Serial.println(String(gnss.getTime().hour)+":"+String(gnss.getTime().minute));
/*
    sunTracker.setLocalisation(gnss.getCoordinates());

    sunTracker.update(31, {10,00});
    sunTracker.update(31, {14,00});
    sunTracker.update(31, {17,00});
*/
    gnss.displayInformations();

    //Serial.println(sunTracker.getAzimut());
    //Serial.println(sunTracker.getElevation());

    
    
  }
  
  // put your main code here, to run repeatedly:

//gnss.simulate();
  //gnss.readData();
  //delay(1000);

}
