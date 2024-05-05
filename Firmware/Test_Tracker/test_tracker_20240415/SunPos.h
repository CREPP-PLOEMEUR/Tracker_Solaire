// calcul de la position du soleil par rapport à la date courante

#ifndef SunPos_h
#define SunPos_h
// #define DEBUG

#include <Arduino.h>
# include <math.h>
#include "commonTypes.h"

// les structures suivantes peuvent aussi avoir été définies dans Neo6mTracker
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



class SunPos{

 
  public:

  // ne fait rien - c'est juste pour initialiser
  SunPos();

  // calcul de l'orientation

  orientation_t calcOrientation(location_t laLocation, date_t laDate, time_t lHeure, int lTimezone );

     
  float calcDaynum( date_t laDate, time_t lheure, int lTimezone );

   private:
    // conversion degre -> radians
    float Rad(float degrees);

    // conversion radian -> degrés
    float Deg(float radians);

    //fonction modulo sur les degrés pour être dans la bonne limite
    float intoRange(int x, int range_min, int range_max);

    // le daynum courant 
    float currentDaynum;

    // le futur daynum pour le prochain calcul
    float nextDaynum;

    //calcul de daynum en fonction des structures précédentes
    /*
      // conversion en gmt decimal
      float greenwichtime  = when.hour  - when.timezone + when.minute/60.0 + when.seconde/3600.0;
      // date du jour en J2000
     float daynum = (
        367 * when.year
        - 7 * (when.year + (when.month + 9) / 12) / 4
        + 275 * when.month / 9
        + when.day
        - 730531.5
        + greenwichtime / 24);
    */

 




};
#endif







