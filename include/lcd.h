#ifndef LCD_H
#define LCD_H

#include <Arduino.h>

class LCD
{
private:
  uint8_t m_CS;
  uint8_t m_DC;
  uint8_t m_RST;
  uint8_t m_SCK;
  uint8_t m_MOSI;
  
  void sendCommand(uint8_t cmd);
  void sendData(uint8_t data);
  void sendDataBuffer(const uint8_t* data, size_t len);
  void drawChar(int x, int y, char c, uint16_t color, uint8_t size);
  void drawString(const char* msg, int x, int y, uint16_t color, uint8_t size);

public:
  LCD(uint8_t cs, uint8_t dc, uint8_t rst, uint8_t sck, uint8_t mosi);
  void init();
  void fillScreen(uint16_t color);
  void drawPixel(int x, int y, uint16_t color);
  void drawStringCentered(const char* str, int screen_width, int screen_height, uint16_t color, uint8_t scale);
  inline uint16_t fixColor(uint16_t color);
  void drawPlayingState(const String& statusTxt, const String& filename);
};

extern LCD lcd;

#endif
