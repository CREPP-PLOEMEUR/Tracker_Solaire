/**
 * @file RGB.h
 * @author Nicolas LE GUERROUE
 * @brief 
 * @version 1.0
 * @date 2023-01-22
 * 
 */
#ifndef RGB_H
#define RGB_H

#include "Arduino.h"

#define RED 0
#define GREEN 1
#define BLUE 2
#define CYAN 3
#define ORANGE 4
#define WHITE 5
#define PURPLE 6
#define TURQUOISE 7
#define YELLOW 8
#define MAGENTA 9
#define ROSE 10

/**
 * @brief RGB class
 * 
 */
class RGB 			
{
public:

/**
 * @brief Construct a new RGB object
 * 
 * @param pin_red 
 * @param pin_green 
 * @param pin_blue 
 */
RGB(int pin_red, int pin_green, int pin_blue);	

/**
 * @brief Power on RGB LED with color
 * 
 * @param color 
 */
void on(int color);

/**
 * @brief Blink RGB LED
 * 
 * @param color 
 * @param delai_high 
 * @param delai_low 
 * @param nombre 
 */
void blink(int color, unsigned long delai_high, unsigned long delai_low,unsigned long nombre);

/**
 * @brief Power off RGB LED
 * 
 */
void off();

/**
 * @brief Function to display random colors
 * 
 * @param delai : delay in ms 
 * @param frequence : in Hz
 */
void randomRGB(unsigned long delai, int frequence);

private:

int pin_redIN;
int pin_greenIN;
int pin_blueIN;

}; 


#endif