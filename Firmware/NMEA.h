#ifndef NMEA_H
#define NMEA_H


#include "Arduino.h"


#define NMEA_DEFAULT_HEADER '$'
#define NMEA_DEFAULT_DELIMITER ','
#define NMEA_DEFAULT_FOOTER '*'


#define NMEA_MAX_DELIMITERS 32

#define NMEA_SOURCE_NUMBER 5
#define NMEA_MESSAGE_TYPE_NUMBER 6

/**
 * @brief NMEA frame
 * 
 */
typedef String NMEA_Frame;


/**
 * @brief N%MEA Settings (header, delimiter and footer)
 * 
 */
typedef struct 
{

    char header;
    char delimiter;
    char footer;

} NMEA_Settings;


typedef struct 
{
    uint8_t countOfDelimiters;
    char indexOfDelimiters[NMEA_MAX_DELIMITERS];

} NMEA_Parser;


typedef struct 
{

    char *source;
    char *name;

} NMEA_Source;




typedef struct 
{

    String name;

} NMEA_MessageType;







#endif