#include "ADC_Tools.h"

ADC_Tools::ADC_Tools() 
{

}

uint16_t ADC_Tools::getValue(uint8_t channel)
{
    return analogRead(m_rawChannels[channel]);
}

ADC_Tools::~ADC_Tools()
{

}
