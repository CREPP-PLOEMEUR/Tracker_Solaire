/**
 * @file UBLOX_7M.h
 * @author Nicolas Le Guerroue
 * @brief 
 * @version 1.0
 * @date 
 * 
 */
#ifndef UBLOX_7M_H
#define UBLOX_7M_H


#define GNSS_MODULE_SLEEP "$PMTK161,0*28"
#define GNSS_MODULE_WAKE_UP "$PMTK010,001*2E"

#define GNSS_MODULE_WAKE_UP "$PMTK010,001*2E"

  inline String GNSS_setUpdateRate(uint16_t delay)
  {
    return "$PMTK220,"+String(1000)+"*1F";
  }



#endif 