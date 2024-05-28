/**
 * @file GNSS.h
 * @author Nicolas Le Guerroue
 * @brief 
 * @version 1.0
 * @date 
 * 
 */
#ifndef NMEA_H
#define NMEA_H

#include "Arduino.h"

/**
 * @brief Start of NMEA frame
 * 
 */

#define NMEA_DEFAULT_HEADER '$'

/**
 * @brief Delimiter of field into NMEA frame
 * 
 */
#define NMEA_DEFAULT_DELIMITER ','

/**
 * @brief End of NMEA frame
 * 
 */

#define NMEA_DEFAULT_FOOTER '*'

/**
 * @brief Max delimiters count in NMEA frame
 * 
 */

#define NMEA_MAX_DELIMITERS 32

/**
 * @brief Count of possible type of NMEA source (type of satellite)
 * 
 */

#define NMEA_SOURCE_NUMBER 5

/**
 * @brief 
 * 
 */

#define NMEA_MESSAGE_TYPE_NUMBER 6

/**
 * @brief NMEA frame (Header, content and footer)
 * 
 */
typedef String NMEA_Frame;


/**
 * @brief NMEA Settings (header, delimiter and footer)
 * 
 */
typedef struct 
{

    char header;
    char delimiter;
    char footer;

} NMEA_Settings;

/**
 * @brief Struct to parse NMEA frame
 * 
 */
typedef struct 
{
    uint8_t countOfDelimiters;
    char indexOfDelimiters[NMEA_MAX_DELIMITERS];

} NMEA_Parser;

/**
 * @brief NMEA source struct
 * 
 */
typedef struct 
{

    char *source;
    char *name;

} NMEA_Source;


/**
 * @brief NMEA message type
 * 
 */
typedef struct 
{

    String name;

} NMEA_MessageType;

#endif