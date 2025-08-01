#include "include/lcd.h"
#include "include/config.h"
#include "include/font5x7.h"
#include <Arduino.h>
#include <SPI.h>

LCD lcd(LCD_CS, LCD_DC, LCD_RST, LCD_SCLK, LCD_MOSI);

LCD::LCD(uint8_t cs, uint8_t dc, uint8_t rst, uint8_t sck, uint8_t mosi)
  : m_CS(cs)
  , m_DC(dc)
  , m_RST(rst)
  , m_SCK(sck)
  , m_MOSI(mosi)
{ }

void LCD::init()
{
  pinMode(m_CS, OUTPUT);
  pinMode(m_DC, OUTPUT);
  pinMode(m_RST, OUTPUT);

  SPI.begin(m_SCK, -1, m_MOSI, m_CS); // SCK, MISO(not used), MOSI, CS
  digitalWrite(m_RST, LOW);
  delay(20);
  digitalWrite(m_RST, HIGH);
  delay(150);

  SPI.begin();

  sendCommand(0x36);
  sendData(0x48);

  sendCommand(0x3A);
  sendData(0x55);

  sendCommand(0x11); // Sleep out
  delay(120);
  sendCommand(0x29);
  // digitalWrite(m_CS, HIGH);
}

inline uint16_t LCD::fixColor(uint16_t color)
{  
  uint8_t r5 = (color >> 11) & 0x1F;
  uint8_t g6 = (color >> 5) & 0x3F;
  uint8_t b5 = color & 0x1F;
  
  uint8_t r8 = (r5 * 255) / 31;
  uint8_t g8 = (g6 * 255) / 63;
  uint8_t b8 = (b5 * 255) / 31;
  
  r8 = 255 - r8;
  g8 = 255 - g8;
  b8 = 255 - b8;
  
  uint8_t new_r = (r8 * 31) / 255;
  uint8_t new_g = (g8 * 63) / 255;
  uint8_t new_b = (b8 * 31) / 255;
  
  return (new_b << 11) | (new_g << 5) | (new_r);
}

void LCD::sendCommand(uint8_t cmd)
{
  digitalWrite(m_DC, LOW);
  SPI.beginTransaction(SPISettings(40000000, MSBFIRST, SPI_MODE0));
  digitalWrite(m_CS, LOW);
  SPI.transfer(cmd);
  digitalWrite(m_CS, HIGH);
  SPI.endTransaction();
}

void LCD::sendData(uint8_t data)
{
  digitalWrite(m_DC, HIGH);
  SPI.beginTransaction(SPISettings(40000000, MSBFIRST, SPI_MODE0));
  digitalWrite(m_CS, LOW);
  SPI.transfer(data);
  digitalWrite(m_CS, HIGH);
  SPI.endTransaction();
}

void LCD::sendDataBuffer(const uint8_t* data, size_t len)
{
  digitalWrite(m_DC, LOW);
  SPI.beginTransaction(SPISettings(40000000, MSBFIRST, SPI_MODE0));
  digitalWrite(m_CS, LOW);
  SPI.writeBytes(data, len);
  digitalWrite(m_CS, HIGH);
  SPI.endTransaction();
}

void LCD::fillScreen(uint16_t color)
{
  color = this->fixColor(color);
  // 320*480 range
  sendCommand(0x36);
  sendData(0x00);

  sendCommand(0x2A); // Column addr set
  sendData(0x00); sendData(0x00);
  sendData(0x01); sendData(0x3F); // 319

  sendCommand(0x2B); // Row addr set
  sendData(0x00); sendData(0x00);
  sendData(0x01); sendData(0xDF); // 479

  sendCommand(0x2C); // Memory write

  uint8_t hi = color >> 8;
  uint8_t lo = color & 0xFF;

  digitalWrite(m_DC, HIGH);
  SPI.beginTransaction(SPISettings(40000000, MSBFIRST, SPI_MODE0));
  digitalWrite(m_CS, LOW);
  for (int i = 0; i < 320 * 480; ++i)
  {
      SPI.transfer(hi);
      SPI.transfer(lo);
  }
  digitalWrite(m_CS, HIGH);
  SPI.endTransaction();
}

void LCD::drawChar(int x, int y, char c, uint16_t color, uint8_t size)
{
  if (c < 32 || c > 126) return;
  const uint8_t* bitmap = font5x7[c - 32];

  color = fixColor(color);

  for (int col = 0; col < 5; ++col)
  {
    uint8_t bits = bitmap[4 - col];
    for (int row = 0; row < 7; ++row)
    {
      if (bits & (1 << row))
      {
        for (int dx = 0; dx < size; ++dx)
        {
          for (int dy = 0; dy < size; ++dy)
          {
            drawPixel(x + col * size + dx, y + row * size + dy, color);
          }
        }
      }
    }
  }
}

void LCD::drawString(const char* str, int x, int y, uint16_t color, uint8_t size)
{
  const int spacing = 1;

  int len = strlen(str);

  for (int i = 0; i < len; ++i)
  {
    drawChar(x, y, str[i], color, size);
    x -= (5 + spacing) * size;
  }
}

void LCD::drawStringCentered(const char* str, int screen_width, int screen_height, uint16_t color, uint8_t size)
{
  const int spacing = 1;
  int len = strlen(str);
  int text_width = ((5 + spacing) * len - spacing) * size;
  int text_height = 7 * size;
  int x = (screen_width - text_width) / 2 + (text_width - 5 * size);
  int y = (screen_height - text_height) / 2;
  
  drawString(str, x, y, color, size);
}

void LCD::drawPlayingState(const String& statusTxt, const String& filename)
{
  lcd.fillScreen(NAVY);
  
  drawStringCentered(filename.c_str(), 320, 20, 0xFFFF, 3);

  drawStringCentered(statusTxt.c_str(), 320, 480, LEMON, 4);

  drawStringCentered("<<   >||   []   >>", 320, 850, WHITE, 2);
}

void LCD::drawPixel(int x, int y, uint16_t color)
{
  sendCommand(0x2A);
  sendData(x >> 8); sendData(x & 0xFF);
  sendData(x >> 8); sendData(x & 0xFF);

  sendCommand(0x2B);
  sendData(y >> 8); sendData(y & 0xFF);
  sendData(y >> 8); sendData(y & 0xFF);

  sendCommand(0x2C);
  sendData(color >> 8); sendData(color & 0xFF);
}