#ifndef ADC_HPP
#define ADC_HPP

#include <Arduino.h>

#define CHANNELS_NUMBER 6

class ADC_Tools
{
private:
    /* data */
    uint8_t m_rawChannels[CHANNELS_NUMBER] = {A0, A1, A2, A3, A4, A5};
public:
    ADC_Tools();
    ~ADC_Tools();
    uint16_t getValue(uint8_t channel);
};



#endif