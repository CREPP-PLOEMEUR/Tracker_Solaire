#ifndef DATETIMESTRUCT
#define DATETIMESTRUCT
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
