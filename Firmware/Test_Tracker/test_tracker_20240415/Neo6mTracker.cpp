// Neo6mTracker
// cette classe encapsule tinyGpsPlusPlus en ne gardant que ce qui nous concerne
// - la position 
// - la date
// - l'heure
// les méthodes attendent que la réponse soit valide, en particulier la position

#include "Neo6mTracker.h"



// initialisation
Neo6mTracker::Neo6mTracker(uint8_t rxPin2, uint8_t txPin2, long gpsSpeed) {
  //static SoftwareSerial ss = SoftwareSerial(rxPin, txPin);
    //pinMode(rxPin, INPUT);
    //pinMode(txPin, OUTPUT);
  //_gpsSpeed = gpsSpeed;

  // SoftwareSerial ss( rxPin, txPin );
  ss = SoftwareSerial(rxPin2, txPin2, false);
  ss.begin(gpsSpeed);

   };

// fonction interne d'acquisition
// attend l'arrivée d'une trame du gps - une ligne à la fois

void Neo6mTracker::my_aquisition() {
  //SoftwareSerial ss( _rxPin, _txPin );
  //  SoftwareSerial ss(2,3);

  //if (ss_init == false ) {
   //     ss.begin(9600);
    ss_init=true;
  //}

   // This sketch displays information every time a new sentence is correctly encoded.

  while (ss.available() > 0){
    // on a reçu une ligne $G.......CR/LF
    gps.encode(ss.read());
    // la classe gps analyse le contenu de cette trame
    if ( gps.location.isValid()  ) {
      // Latitude in degrees (double)
       my_location.lat = gps.location.lat();
       my_location.lng = gps.location.lng();
    }
    
    if ( gps.time.isValid()  ) {
      my_time.hour = gps.time.hour();
      my_time.minute = gps.time.minute();
      my_time.seconde = gps.time.second();
    }

    if ( gps.date.isValid()  ) {
      my_date.year = gps.date.year();
      my_date.month = gps.date.month();
      my_date.day = gps.date.day();
    }
/*
      // Number of satellites in use (u32)
      Serial.print(" .... Number of satellites in use = "); 
      Serial.println(gps.satellites.value()); 

   // Horizontal Dim. of Precision (100ths-i32)
      Serial.print("HDOP = "); 
      Serial.println(gps.hdop.value()); 
*/
    
  }

};



// donne les valeurs courantes de la structure location;
location_t  Neo6mTracker::getLocation() {
  location_t retour;
  // Serial.println("getLocation");
  // tant que la location ne correspond pas à un créneau valide pour nous
  // sur les premières trames on peut avoir des valeurs complement loufoques
  while (  (my_location.lat < 30.0)  || (my_location.lat > 60.0) 
        || (my_location.lng < -45.0) || (my_location.lng < -45.0) ){
      // my_acquisition met à jour la structure privée;
      my_aquisition();
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
date_t Neo6mTracker::getDate(){
  date_t retour;
  //  Serial.println("getDate");
  // tant que la date ne correspond pas à un créneau valide pour nous
  // sur les premières trames on peut avoir des valeurs complement loufoques

  while ( (my_date.year < 2000) || (my_date.year > 2200) 
  || (my_date.month < 1) || (my_date.month > 12) 
  || (my_date.day < 1) || (my_date.day > 31)   ) {
   my_aquisition();
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
time_t Neo6mTracker::getTime(){
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
   my_aquisition();
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
