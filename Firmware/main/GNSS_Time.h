/**
 * @file GNSS_TIME.h
 * @author Nicolas Le Guerroue
 * @brief 
 * @version 1.0
 * @date 
 * 
 */
#ifndef GNSS_TIME
#define GNSS_TIME


#include "Arduino.h"

typedef struct 
{
  uint8_t hour;
  uint8_t minute;
  uint8_t seconde;
} GNSS_Time;

typedef struct 
{
  uint8_t day;
  uint8_t month;
  uint8_t year; //23
} GNSS_Date;

#endif