#ifndef DATETIME_H
#define DATETIME_H


#include "Arduino.h"

typedef struct 
{
  uint8_t hour;
  uint8_t minute;
  uint8_t seconde;
} DateTime;

typedef struct 
{
  uint8_t day;
  uint8_t month;
  uint8_t year; //23
} Date;

#endif