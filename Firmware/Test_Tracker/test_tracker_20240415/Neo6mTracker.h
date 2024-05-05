// Neo6mTracker
// cette classe encapsule tinyGpsPlusPlus en ne gardant que ce qui nous concerne
// - la position 
// - la date
// - l'heure
// les méthodes attendent que la réponse soit valide, en particulier la position

#ifndef Neo6mTracker_h
#define Neo6mTracker_h
// #define DEBUG

#include <Arduino.h>

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "commonTypes.h"

/*
#ifndef DATETIMESTRUCT
#define DATETIMESTRUCT
// les mêmes structures sont aussi dans le calcul d'orientation 
// pas dans la class
    typedef struct {
      uint16_t year;
      uint8_t month;
      uint8_t day;
      } date_t;

    typedef struct {
      uint8_t hour;
      uint8_t minute;
      uint8_t seconde;
      } time_t;

    typedef struct { 
      double lat;
      double lng;
      }  location_t;

  // specifique à cette classe
  typedef struct {
    float azimuth;
    float elevation;
  } orientation_t;
  
  #endif
*/


class Neo6mTracker {

   public:


    // initialisation de la connexion
    Neo6mTracker(uint8_t rxPin2, uint8_t txPin2, long gpsSpeed);

    // donne les valeurs courantes de la structure location;
    location_t  getLocation();

    // donne les valeurs courantes de la structure date
    date_t getDate();

    // donne les valeurs courantes de la strucurre time;
    time_t getTime();
    
     private:
    // The TinyGPS++ object
    TinyGPSPlus gps;

    SoftwareSerial ss = SoftwareSerial(2,3); // (GPS_RX, GPS_TX);

    boolean ss_init = false;

    // structures locales recevant les mises à jour
    date_t my_date;
    time_t my_time;
    location_t my_location;

    // effectue une acquisition des valeurs depuis le gps et met à jour les structures my_date, my_time et my_location
    void my_aquisition(); 

};

#endif

