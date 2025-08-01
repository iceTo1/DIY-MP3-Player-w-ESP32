#ifndef CONFIG_H
#define CONFIG_H

// Buttons
#define STOP_BUTTON       21
#define NEXT_SONG_BUTTON  22
#define PLAY_PAUSE_BUTTON 17
#define PREV_SONG_BUTTON  16

// LCD
#define LCD_CS     4
#define LCD_DC     27
#define LCD_RST    14
#define LCD_SCLK   18
#define LCD_MOSI   23

// SD Card
#define SD_CS_PIN  5
#define SD_SCK_PIN 18
#define SD_MOSI    23
#define SD_MISO    19

// PCM5102
#define I2S_NUM    I2S_NUM_0
#define I2S_BCK    26 // BCK
#define I2S_WS     33 // LCK
#define I2S_DATA   25  // DIN

// Colors
#define RED        0xF800
#define BLUE       0x001F
#define NAVY       0x0010
#define LEMON      0xFFE0
#define BLACK      0x0000
#define WHITE      0xFFFF
#define GREEN      0x07E0

#endif