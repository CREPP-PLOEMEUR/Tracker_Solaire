

#include "Display.h"


Display::Display(uint16_t width, uint16_t height, uint8_t address) : m_width{width}, m_height{height}, m_address{address}
{
    m_display = new Adafruit_SSD1306(m_width, m_height, &Wire, -1);
}

void Display::init()
{
  m_display->begin(SSD1306_SWITCHCAPVCC, m_address);
  m_display->clearDisplay();
  m_display->setTextSize(0.5);
  m_display->setTextColor(WHITE);
  m_display->setCursor(0, 0);

}

void Display::print(String text)
{

  m_display->print(text);
  m_display->display();
  m_currentLine++;
  if(m_currentLine >=4)
  {
    m_currentLine=0;
  }

}

void Display::printcl(String text)
{
  m_display->clearDisplay();
  m_display->setCursor(0, 0);
  m_display->print(text);
  m_display->display();

}


void Display::clear(void)
{
  m_display->clearDisplay();
  m_display->setCursor(0, 0);
  m_display->display();

}

void Display::println(String text)
{
  m_display->println(text);
  m_display->display();
}


Display::~Display()
{
}