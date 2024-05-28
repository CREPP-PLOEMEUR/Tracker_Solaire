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

  inline String GNSS_setUpdateRate()
  {
    return "$PUBX,41,1,0007,0003,5000,0*25\r\n";
  }



#endif 