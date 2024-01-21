/**
 * @file GNSS_COORDINATES.h
 * @author Nicolas Le Guerroue
 * @brief 
 * @version 1.0
 * @date 
 * 
 */
#ifndef GNSS_COORDINATES_H
#define GNSS_COORDINATES_H

typedef struct 
{
  float latitude;
  float longitude;      
  char latitudeDirection; 
  char longitudeDirection;
} GNSS_Coordinates;


#endif 

