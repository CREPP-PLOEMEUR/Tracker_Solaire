//#include <SoftwareSerial.h>
#include <SoftwareSerial.h>
#include "ConnectionPins.h"
#include "commonTypes.h"
#include "SunPos.h"


#include "Neo6mTracker.h"
#include "ElevationMotor.h"
// #include "Oled1306.h"
#include "AzimutMotor.h"

/*
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
*/

/*
long GPS_Speed=9600;
uint8_t myGPS_RX=2;  // broche RX pour l'arduino
uint8_t myGPS_TX=3;  // broche TX pour l'arduino

// pour le vérin d'élévation pint en H
uint8_t elevEnable=5;   // broche Enable - output Active High
uint8_t elevIN_A=6;     // broche IN_A - output Active High
uint8_t elevIN_B=7;     // broche IN_B - output Active High

uint8_t  elevPotar=A0;  // mesure du potentiomètre Input Analog 

*/


Neo6mTracker myNeo6m(myGPS_RX,myGPS_TX,GPS_Speed );

ElevationMotor ElevMotor(elevEnable, elevIN_A, elevIN_B, elevPotar );
/* AzimutMotor::AzimutMotor(uint8_t enaPin, uint8_t pulsePin, uint8_t dirPin, uint8_t buteePin)
uint8_t tb66DirPin = 8;  // Broche Dir   - output Active High
uint8_t tb66PulsePin = 9; // Broche Pulse  - output Active High
uint8_t tb66EnaPin = 10; // broche Enable -  - output Active High

uint8_t tb66ButeePin=11;  // Broche Capteur fin de course Retour - Active Low
*/
AzimutMotor AzimMotor(tb66EnaPin,tb66PulsePin,tb66DirPin,tb66ButeePin);

SunPos mySunPos;

date_t dateret;
time_t timeret;
location_t locret;
orientation_t orientationret;
float daynum;
char affString[80];

int myTimezone=0;

int prochaine_minute=0;
int interval=10;
bool premier_lancement=true;

float elevationCalcul = 30.0;
float azimutCalcul=0.0;

int localpas=0;

void prochain_trt(){
  prochaine_minute = (timeret.minute + interval) %60;
  sprintf(affString,"**************   prochain trt à %02d *******************",prochaine_minute);
  Serial.println(affString);
  Serial.flush();
}


void setup(){

  float aa=90.0;
 
  Serial.begin(115200);
  // oledinit();
  delay(200);

  //elevationCalcul = ElevMotor.setAngle(30.0);

  //localpas = AzimMotor.versOuest(200);
  //delay(2000);
  localpas = AzimMotor.retourEst();
  delay(2000);
  azimutCalcul = AzimMotor.getAngle();
  Serial.println(azimutCalcul,2);
  delay(2000);
/*
  tests
  for (int i=1;i<7;i++){
    aa=90.5 + i*30.0;
    Serial.println(aa,2);

    azimutCalcul = AzimMotor.setAngle(aa);

      delay(2000);
  }
*/


};

void loop() {

  Serial.println(" - - - - - - - - \n");

 
  //oledaffClear();

timeret  = myNeo6m.getTime();
    //  oledaffHeure(timeret);
      sprintf(affString,"H: %02d:%02d:%02d  prochain à %02d",timeret.hour,timeret.minute,timeret.seconde,prochaine_minute);
      Serial.println(affString);



 dateret = myNeo6m.getDate();
      // oledaffDate(dateret);
      sprintf(affString,"D: %4d/%02d/%02d",dateret.year,dateret.month,dateret.day);
      Serial.println(affString);

  locret = myNeo6m.getLocation();
      // oledaffLocation(locret);
      Serial.print("Lat:");
      Serial.print(locret.lat,3);
      Serial.print("  Lng:");
      Serial.println(locret.lng,3);

  

  
  // daynum = mySunPos.calcDaynum(dateret, timeret);


  orientationret = mySunPos.calcOrientation(locret, dateret, timeret,myTimezone);
     // oledaffOrientation(orientationret);
       Serial.print("Azm:");
      Serial.print(orientationret.azimuth,2);
      Serial.print("  elv:");
      Serial.println(orientationret.elevation,2);

  if (premier_lancement) {
    prochain_trt();
     Serial.print("premiere Elevation : ");
    Serial.println(orientationret.elevation,2);
    // elevationCalcul = ElevMotor.setAngle(orientationret.elevation);
    azimutCalcul = AzimMotor.setAngle(orientationret.azimuth);
    premier_lancement = false;

  }

  if (timeret.minute == prochaine_minute) {
    // prochaine opération planfifiée
    prochain_trt();

    Serial.print("elevation.setAngle() ");
    Serial.println(orientationret.elevation,2);
    Serial.flush();
    // elevationCalcul = ElevMotor.setAngle(orientationret.elevation);

    azimutCalcul = AzimMotor.setAngle(orientationret.azimuth);
    

    Serial.print("azimuth.setAngle() ");
    Serial.println(orientationret.azimuth,2);
    Serial.flush();

    }
  

  Serial.print(" Angle :");
  Serial.println(AzimMotor.getAngle(),2);
  Serial.print(" Pas :");
  Serial.print(AzimMotor.getPas());
  Serial.print(" - micros ");
  Serial.println(micros());
  Serial.flush();

  //for(;;);

  delay(10000);

  };