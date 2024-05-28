// NeoTracker
// cette classe encapsule tinyGpsPlusPlus en ne gardant que ce qui nous concerne
// - la position 
// - la date
// - l'heure
// les méthodes attendent que la réponse soit valide, en particulier la position

#include "NeoTracker.h"

#define BLINK_EN_C digitalWrite(5,1);delay(50);digitalWrite(5,0);

// initialisation
NeoTracker::NeoTracker(long gpsSpeed) 
{
  Serial.begin(gpsSpeed);
};


// NeoTracker::addTerminal(Display *display) 
// {
//   m_display_debug = display;
// };



void NeoTracker::update() 
{
 
  while (Serial.available() > 0)
  {
    
    gps.encode(Serial.read());
    // la classe gps analyse le contenu de cette trame
    if ( gps.location.isValid()  ) 
    {
      // Latitude in degrees (double)
       my_location.lat = gps.location.lat();
       my_location.lng = gps.location.lng();
       BLINK_EN_C;
    }
    
    if ( gps.time.isValid()  ) {
      my_time.hour = gps.time.hour();
      my_time.minute = gps.time.minute();
      my_time.seconde = gps.time.second();
      BLINK_EN_C;
    }

    if ( gps.date.isValid()  ) {
      my_date.year = gps.date.year();
      my_date.month = gps.date.month();
      my_date.day = gps.date.day();
      BLINK_EN_C;
    }
    
  }

};



// donne les valeurs courantes de la structure location;
location_t  NeoTracker::getLocation() {
  location_t retour;
  // Serial.println("getLocation");
  // tant que la location ne correspond pas à un créneau valide pour nous
  // sur les premières trames on peut avoir des valeurs complement loufoques
  while (  (my_location.lat < 30.0)  || (my_location.lat > 60.0) 
        || (my_location.lng < -45.0) || (my_location.lng < -45.0) ){
      // my_acquisition met à jour la structure privée;
      update();
      }

      retour.lat = my_location.lat;
      retour.lng = my_location.lng;

      #ifdef DEBUG_GPS
       Serial.print("-> Latitude= "); 
      // Serial.print(gps.location.lat(), 6);      
      Serial.print(retour.lat, 6);
      // Longitude in degrees (double)
      Serial.print(":  Longitude= "); 
      //Serial.println(gps.location.lng(), 6);
      Serial.println(retour.lng, 6);
      #endif
     

    return retour;
  };

  // donne les valeurs courantes de la structure date
date_t NeoTracker::getDate(){
  date_t retour;
  //  Serial.println("getDate");
  // tant que la date ne correspond pas à un créneau valide pour nous
  // sur les premières trames on peut avoir des valeurs complement loufoques

  while ( (my_date.year < 2000) || (my_date.year > 2200) 
  || (my_date.month < 1) || (my_date.month > 12) 
  || (my_date.day < 1) || (my_date.day > 31)   ) {
   update();
  }
 
    retour.year = my_date.year;
    retour.month = my_date.month;
    retour.day = my_date.day;

    //ça serait bien de mettre un #ifdef DEBUG
    #ifdef DEBUG_GPS
      Serial.print("-> Year = "); 
      Serial.print(retour.year);
      Serial.print(", Month = "); 
      Serial.print(retour.month); 
      Serial.print(", Day = "); 
      Serial.println(retour.day);
      #endif
      

    return retour;
  };

// donne les valeurs courantes de la strucurre time;
time_t NeoTracker::getTime(){
  time_t retour;
  // Serial.println("getTime");
  // memorisation de la valeur avant nouvelle acquisition
  uint8_t sec = my_time.seconde;
    // tant que l'heure ne correspond pas à un créneau valide pour nous
  // sur les premières trames on peut avoir des valeurs complement loufoques
  // et si les secondes n'ont pas changées
 while ( (my_time.hour < 0) || (my_time.hour > 23) 
  || (my_time.minute < 0) || (my_time.minute > 59) 
  || (my_time.seconde < 0) || (my_time.seconde > 59) || (my_time.seconde == sec )   ) {
   update();
  }

    retour.hour = my_time.hour;
    retour.minute = my_time.minute;
    retour.seconde = my_time.seconde;

    #ifdef DEBUG_GPS
      Serial.print("-> Hour = "); 
      Serial.print(retour.hour);
      Serial.print(":"); 
      Serial.print(retour.minute); 
      Serial.print(":"); 
      Serial.println(retour.seconde);
     #endif
      
  return retour;

};
