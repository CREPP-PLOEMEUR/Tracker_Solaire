#include "PCA9536.h"


PCA9536::PCA9536()
{
   //Do nothing
}


static inline uint8_t __PINS_2_BYTE(uint8_t pins)
{

}

void PCA9536::begin()
{
  
}


void PCA9536::pinMode(uint8_t pin, uint8_t mode)
{
  Wire.beginTransmission(this->m_adress);
  Wire.write(mode);  // Sélection du registre de configuration
  Wire.write(0x00);          // Écrire la configuration (0x00 : toutes les broches en sortie)
  Wire.endTransmission();
}

uint8_t PCA9536::digitalRead(uint8_t pin)
{
  Wire.beginTransmission(this->m_adress);
  Wire.write(PCA9536_INPUT);  // Sélection du registre d'entrée
  Wire.endTransmission();

  //Get 1 byte
  Wire.requestFrom(int(this->m_adress), int(1));
  return Wire.read();  // Lire l'état des broches
}

void PCA9536::digitalWrite(uint8_t pins, bool value)
{
  //uint8_t pin = __PINS_2_BYTE(pins);
  
  Wire.beginTransmission(this->m_adress);
  Wire.write(PCA9536_OUTPUT);  // Sélection du registre de sortie
  Wire.write(value);                // Écrire la valeur (0x0F pour activer toutes les broches)
  Wire.endTransmission();
}