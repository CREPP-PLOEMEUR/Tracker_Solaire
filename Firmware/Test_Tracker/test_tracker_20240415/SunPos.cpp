#include "HardwareSerial.h"
// calcul de la position du soleil en fonction de la position, la date et l'heure
#include "SunPos.h"


SunPos::SunPos() {
  currentDaynum = 0.0;
};

float SunPos::Rad(float degrees){
  return  (degrees * 71) / 4068;
};

    // conversion radian -> degrés
float SunPos::Deg(float radians){
  return (radians * 4068) / 71;
};


//fonction modulo sur les degrés pour être dans la bonne limite
float SunPos::intoRange(int x, int range_min, int range_max) {
    int shiftedx = x - range_min;
    int delta = range_max - range_min;
    return ((((shiftedx % delta) + delta) % delta) + range_min);
};

/* code python
   daynum = (
        367 * year
        - 7 * (year + (month + 9) // 12) // 4
        + 275 * month // 9
        + day
        - 730531.5
        + greenwichtime / 24
    )
*/

float SunPos::calcDaynum( date_t laDate, time_t lHeure, int lTimezone ){
  // ne tient pas compte d'un timezone, le GPS fournit l'heure en GMT
  float greenwichtime  = (lHeure.hour + lTimezone)*1.0 + lHeure.minute/60.0 + lHeure.seconde/3600.0;

  Serial.print("greenwichtime :");
  Serial.print(greenwichtime,6);
  //
  long fyear =  laDate.year;  // intermédiare year est un uint16_t  mais le résultat *367 doit être un long
  int fmonth = laDate.month ;
  int fday  = laDate.day ;

/* // debug - a comparer avec le code python
  Serial.println(" | ");
  Serial.print(     367 * fyear);
  Serial.println(" | ");
  Serial.print(      - 7 * (fyear + (fmonth + 9) /12) /4);
  Serial.println(" | ");
  Serial.print(      + 275 * fmonth / 9);
  Serial.println(" | ");
  Serial.print(      + fday);
  Serial.println(" | ");
  Serial.print(      - 730531.5);
  Serial.println(" | ");
  Serial.print(      + greenwichtime / 24);
Serial.println(" | ");
*/
 // date du jour en J2000
  double daynum = (
        367 * fyear
        - 7 * (fyear + (fmonth + 9) /12) /4
        + 275 * fmonth / 9
        + fday
        - 730531.5
        + greenwichtime / 24
    );

 
  /* float daynum = (
        367.0 * laDate.year
        - 7.0 * (laDate.year*1.0 + (laDate.month + 9.0) / 12.0) / 4.0
        + 275.0 * laDate.month / 9.0
        + laDate.day * 1.0
        - 730531.5
        + (greenwichtime / 24)
      );
  */
   Serial.print(", daynum =>");
   Serial.println(daynum,6);

  return daynum;

};

orientation_t SunPos::calcOrientation(location_t laLocation, date_t laDate, time_t lHeure, int lTimezone  ){
  orientation_t resultat;

  // Convert latitude and longitude to radians
    float rlat = Rad(laLocation.lat);
    float rlon = Rad(laLocation.lng);

    currentDaynum = calcDaynum(laDate, lHeure,lTimezone);

    // Mean longitude of the sun
    float mean_long = currentDaynum * 0.01720279239 + 4.894967873;
    // Mean anomaly of the Sun
    float mean_anom = currentDaynum * 0.01720197034 + 6.240040768;
    // Ecliptic longitude of the sun
    float eclip_long = (
        mean_long
        + 0.03342305518 * sin(mean_anom)
        + 0.0003490658504 * sin(2 * mean_anom)
        );
    // Obliquity of the ecliptic
    float obliquity = 0.4090877234 - 0.000000006981317008 * currentDaynum;
    // Right ascension of the sun
    float rasc = atan2(cos(obliquity) * sin(eclip_long), cos(eclip_long));
    // Declination of the sun
    float decl = asin(sin(obliquity) * sin(eclip_long));
    // Local sidereal time
    float sidereal = 4.894961213 + 6.300388099 * currentDaynum + rlon;
    // Hour angle of the sun
    float hour_ang = sidereal - rasc;
    // Local elevation of the sun
    resultat.elevation = asin(sin(decl) * sin(rlat) + cos(decl) * cos(rlat) * cos(hour_ang));

    // Local azimuth of the sun
    resultat.azimuth = atan2(
        -cos(decl) * cos(rlat) * sin(hour_ang),
        sin(decl) - sin(rlat) * sin(resultat.elevation)
        );

// Convert azimuth and elevation to degrees
   resultat.azimuth = intoRange(Deg(resultat.azimuth), 0, 360);
    resultat.elevation = intoRange(Deg(resultat.elevation), -180, 180);
//    azimuth = deg(azimuth);
//    elevation = deg(elevation);

return resultat;

};
