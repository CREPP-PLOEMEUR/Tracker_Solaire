/**
 * @file PCA9536.h
 * @author Nicolas Le Guerroue
 * @brief 
 * @version 1.0
 * @date 
 * 
 */
#ifndef PCA9536_H
#define PCA9536_H

#include <Wire.h>

#define PCA9536_ADDRESS 0x41

//Registers

#define PCA9536_PIN_0 0x01  
#define PCA9536_PIN_1 0x02  
#define PCA9536_PIN_2 0x04  
#define PCA9536_PIN_3 0x08  

#define PC9536_HIGH 0x0F

#define PC9536_LOW 0x00

#define PCA9536_INPUT  0x00
#define PCA9536_OUTPUT 0x01
#define PCA9536_POLARITY    0x02
#define PCA9536_CONFIG      0x03


class PCA9536
{
  
  public:

  PCA9536();
  void begin();


  void pinMode(uint8_t pins, uint8_t mode);
  
  uint8_t digitalRead(uint8_t pin);

  void digitalWrite(uint8_t pins, bool value);

  private:

  uint8_t m_adress = 0x41;
};
#endif 