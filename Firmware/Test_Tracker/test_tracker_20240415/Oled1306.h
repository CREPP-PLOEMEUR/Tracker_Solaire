// Affichage sur ecran OLED type SSD1306 128x64 (16x8 caractères)

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "commonTypes.h"

// Uno R3
// SDA - pin A4
// SCL - pin A5

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)


// 
//Adafruit_SSD1306 display(-1); //SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// Adafruit_SSD1306 display(128, 32, &Wire, -1);

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

static bool _displayIsValid=true;

void oledinit() {

  //delay(2000);
  // display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // Serial.println(i);
 if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    _displayIsValid=false;

    // for(;;); // Don't proceed, loop forever

  }
      
display.clearDisplay();
display.setTextSize(1);
// display.setFont(ArialMT_Plain_8);
  
};


// force un effacement 
  void oledaffClear() {
    if (_displayIsValid ) {
       display.clearDisplay();

    }
  };

  void oledaffAffiche(){
    if (_displayIsValid ) {
       display.display();
    }
  };

   // affiche une chaine formattée par sprintf pas plus de 16 caractères
  // 0123456789ABCDEF
  // Heur- HH:MI:SS
  // Date- DD/MM/YYYY
  // Long- =DD.xxxxx  (signé)
  // Lat - =DD.xxxxx
  // Azim- =DD.xxxxx
  // Elvt- =DD.xxxxx 
  // setcursor x : 1..128, y : 1..32
  void oledaffHeure( time_t lheure){
   char ligne[16];
    sprintf(ligne,"%02d:%02d:%02d  ",lheure.hour,lheure.minute,lheure.seconde);
     if (_displayIsValid ) {
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      // Display static text
      display.println(ligne);
      display.display();
     }
  }; 

  void oledaffDate( date_t laDate){
   char ligne[16];
   sprintf(ligne,"%02d/%02d/%04d",laDate.day, laDate.month, laDate.year);
     if (_displayIsValid ) {
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(62, 0);
      // Display static text
      display.println(ligne);
      display.display();
     }
  }; 

  void oledaffLocation (location_t laLocation){
   
     if (_displayIsValid ) {
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,8);
      // Display static text
      display.print("                 ");
      display.setCursor(0,8);
      display.print("Pos ");
      display.print(laLocation.lat,3);
      display.setCursor(60,8);
      display.print(" , ");
      display.print(laLocation.lng,3);

      display.display();
     }
  }; 

  void oledaffOrientation (orientation_t lOrientation){

     if (_displayIsValid ) {
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,16);
      // Display static text
      display.print("                 ");
      display.setCursor(0,16);
      display.print("Ort ");
       display.print(lOrientation.azimuth,2);
      display.setCursor(60,16);
      display.print(" , ");
       display.print(lOrientation.elevation,2);

      display.display();
     }
  }; 

  // affiche sur les 2 lignes du bas
  void oledaffError( char myCode[6], char myMessage[16]) {
   char ligne[16];
   sprintf(ligne,"Err - %s",myCode);
     if (_displayIsValid ) {
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,24);
      // Display static text
      display.println(ligne);
      display.setCursor(62,24);
      // Display static text
      display.println(myMessage);

      display.display();
     }
  }; 

