//#include <SoftwareSerial.h>
//#include <SoftwareSerial.h>
//#include "ConnectionPins.h"
//#include "commonTypes.h"
//#include "SunPos.h"

#include "AzimutMotor.h"


#include "Settings.h"

#include "Display.h"
#include "ADC_Tools.h"
#include "ConnectionPins.h"

#include "SunTracker.h"
#include "GNSS_Coordinates.h"
#include "GNSS_Time.h"
#include "GNSS.h"                                                    
#include <TinyGPSPlus.h>

#include "PCA9536.h"

#define BLINK_EN_A digitalWrite(4,1);delay(100);digitalWrite(4,0);delay(100);
#define BLINK_EN_B digitalWrite(5,1);delay(100);digitalWrite(5,0);delay(100);


#include <Wire.h>

#include <Wire.h>
#include <RTClib.h>
// Création d'une instance TinyGPS++
TinyGPSPlus gps;
PCA9536 io_Extender;

// Création d'une instance SoftwareSerial pour communiquer avec le module GPS
SoftwareSerial ss(7,6); // RX, TX


#define PCA9536_ADDRESS 0x41 // Adresse I2C du PCA9536D



//#include "ElevationMotor.h"



#define CHANNEL_POT 1


//ElevationMotor ElevMotor(elevEnable, elevIN_A, elevIN_B, elevPotar );
AzimutMotor AzimMotor(tb66EnaPin,tb66PulsePin,tb66DirPin,tb66ButeePin);

Display terminal(128,32, 0x3C);
ADC_Tools adc;

CityLocalisation city = {0,0, 0, 0};
SunTracker sunTracker(city);

//GNSS gnss(7, 6, 9600);

RTC_DS1307 rtc;


/*!
*/
GNSS_Date gnss_date;
GNSS_Time gnss_time;
GNSS_Coordinates gnss_coordinates;



 void setup()
 {

    Serial.begin(9600);
    io_Extender.begin();
    //


    Serial.println("INIT : OK");
    ss.begin(9600);
    terminal.init();
    Wire.begin();  // Initialisation du bus I2C

    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);


    BLINK_EN_A;
    BLINK_EN_B;

    
   
    //gnss.init();
    // gnss.startGNSS();
    //gnss.setDebugChannel(&Serial, 9600);

    //configurePCA9536(0x00);

    //rtc.writeSqwPinMode(DS1307_SquareWave1HZ);
    io_Extender.pinMode(PCA9536_PIN_0,PCA9536_OUTPUT);

    io_Extender.digitalWrite(PCA9536_PIN_0,PC9536_HIGH);

    terminal.println("SELF-TEST : OK");
    Serial.println("SELF-TEST : OK");
    //writePCA9536(0x0F); // Met toutes les broches en état haut (HIGH)
    delay(500);
    io_Extender.digitalWrite(PCA9536_PIN_0,PC9536_LOW);
    //writePCA9536(0x00); // Met toutes les broches en état bas (LOW)

    delay(100);

    Serial.println("RTC : OK");
    rtc.begin();
    delay(100);
    rtc.writeSqwPinMode(DS1307_SquareWave1HZ); // Configurer pour une onde carrée de 1 Hz


    terminal.println("WAITING GNSS..");

    while (ss.available() > 0) {
    gps.encode(ss.read()); // Transfert des données au parser TinyGPS++

    // Si une nouvelle localisation est disponible
    if (gps.location.isUpdated()) {
      Serial.print("Latitude  : ");
      Serial.println(gps.location.lat(), 6);
      Serial.print("Longitude : ");
      Serial.println(gps.location.lng(), 6);
    }

    // Si une nouvelle information temporelle est disponible
    if (gps.time.isUpdated()) {
      Serial.print("Heure     : ");
      Serial.print(gps.time.hour());
      Serial.print(":");
      Serial.print(gps.time.minute());
      Serial.print(":");
      Serial.println(gps.time.second());
    }

    // Si une nouvelle altitude est disponible
    if (gps.altitude.isUpdated()) {
      Serial.print("Altitude  : ");
      Serial.print(gps.altitude.meters());
      Serial.println(" m");
    }

    // Si une nouvelle vitesse est disponible
    if (gps.speed.isUpdated()) {
      Serial.print("Vitesse   : ");
      Serial.print(gps.speed.kmph());
      Serial.println(" km/h");
    }

    Serial.println();
  }

  
    // while( (gnss_time.hour == 0) || (gnss_time.minute == 0))
    // {
      
    //   //gnss_time = gnss.getTime();
    // }
   //gnss.readData();
    Serial.println("END");
    //terminal.println("TIME");
    //terminal.println(String(gnss_date.day)+"/"+String(gnss_date.month)+"/"+String(gnss_date.year)+" - "+ String(gnss_time.hour)+":"+String(gnss_time.minute));




    //Position OK

    
    // bool isReady = false;


    // while( isReady == false)
    // {
    //   gnss.readData();
    //   isReady = gnss.isReady();
    //   BLINK_EN_A;
    //   delay(1000);
    //   BLINK_EN_A;
    //   delay(1000);
    //   BLINK_EN_A;
    //   delay(1000);
    //   BLINK_EN_B;
    //   delay(200);
    //   BLINK_EN_A;
    //   delay(500);
    // }   
    // gnss_coordinates = gnss.getCoordinates();

    // terminal.println(String(gnss_coordinates.latitude,5)+String(gnss_coordinates.latitudeDirection));
    // terminal.println(String(gnss_coordinates.longitude,5)+String(gnss_coordinates.longitudeDirection));
  

 }

 void loop()
 {

  static bool isRunning = false;

    if(analogRead(A1)>800)
    {
      AzimMotor.enableDevice();
      AzimMotor.makeSteps(400, DIRECTION_EST) ;
      //terminal.println("Est");
    }
    else if(analogRead(A1)<200)
    {
      AzimMotor.enableDevice();
       AzimMotor.makeSteps(400, DIRECTION_WEST) ;
       //terminal.println("West");
    }
    else
    {
      AzimMotor.disableDevice();
    }
    //delay(500);

    //BLINK_EN_A;
 }


// void configurePCA9536(uint8_t config) {
//   Wire.beginTransmission(PCA9536_ADDRESS);
//   Wire.write(PCA9536_CONFIG);  // Sélection du registre de configuration
//   Wire.write(config);          // Écrire la configuration (0x00 : toutes les broches en sortie)
//   Wire.endTransmission();
// }

// // Fonction pour écrire des données sur le port de sortie du PCA9536
// void writePCA9536(uint8_t value) {
//   Wire.beginTransmission(PCA9536_ADDRESS);
//   Wire.write(PCA9536_OUTPUT_PORT);  // Sélection du registre de sortie
//   Wire.write(value);                // Écrire la valeur (0x0F pour activer toutes les broches)
//   Wire.endTransmission();
// }

// Fonction pour lire l'état des broches d'entrée du PCA9536
// uint8_t readPCA9536() {
//   Wire.beginTransmission(PCA9536_ADDRESS);
//   Wire.write(PCA9536_INPUT_PORT);  // Sélection du registre d'entrée
//   Wire.endTransmission();

//   Wire.requestFrom(PCA9536_ADDRESS, 1);
//   return Wire.read();  // Lire l'état des broches
// }


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
/*




ElevationMotor ElevMotor(elevEnable, elevIN_A, elevIN_B, elevPotar );
*/
/* AzimutMotor::AzimutMotor(uint8_t enaPin, uint8_t pulsePin, uint8_t dirPin, uint8_t buteePin)
uint8_t tb66DirPin = 8;  // Broche Dir   - output Active High
uint8_t tb66PulsePin = 9; // Broche Pulse  - output Active High
uint8_t tb66EnaPin = 10; // broche Enable -  - output Active High

uint8_t tb66ButeePin=11;  // Broche Capteur fin de course Retour - Active Low

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
/*

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

  */


