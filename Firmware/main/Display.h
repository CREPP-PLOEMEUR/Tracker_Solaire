#ifndef DISPLAY_HPP
#define DISPLAY_HPP



#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


class Display
{
private:
    /* data */

    Adafruit_SSD1306 *m_display;
    uint16_t m_width = 128;
    uint16_t m_height = 64;
    uint8_t m_address = 0x3C;

    uint8_t m_currentLine = 0;

public:
    Display(uint16_t width, uint16_t height, uint8_t address);
    ~Display();

    void init(void);
    void print(String text);
    void printcl(String text);
    void println(String text);
    void clear(void);
};




#endif