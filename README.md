# DIY-MP3-Player-w-ESP32
As my first embedded project, I attempted to build a basic MP3 player using an MCU, an SD Card module, an LCD Screen, a DAC module, and Input buttons.

## ✅ Features
- Play, pause, stop, next, previous functionality using buttons
- WAV playback via PCM5102 (I2S)
- SD card file navigation
- LCD display for basic UI

## 📦 Hardware Used
- ESP32-WROOM-32
- PCM5102A (I2S DAC)
- ST7796 3.5" LCD (SPI)
- MicroSD card & Module w/ level shifter (SPI)
- 4 push buttons

## 🧰 Libraries Required
- `SPI.h`, `Wire.h`, `SD.h`, `FS.h`
- `I2S` for audio
### File Directory
```
esp_player/
├── include/
│   ├── audio.h
│   ├── buttons.h
│   ├── config.h
│   ├── font5x7.h
│   ├── lcd.h
│   ├── sd_card.h
│   └── utils.h
├── src/
│   ├── audio.cpp
│   ├── buttons.cpp
│   ├── font5x7.cpp
│   ├── lcd.cpp
│   ├── sd_card.cpp
│   └── utils.cpp
├── esp_player.ino
```

## 🔌 Wiring Diagram
<img width="2195" height="1966" alt="mp3_diagram" src="https://github.com/user-attachments/assets/cae684d2-8283-4431-97b4-f80785a6cf20" />

### Pin Configurations

**SD Card**
- CS - GPIO 5
- SCK - GPIO 18
- MOSI - GPIO 23
- MISO - GPIO 19
- VCC - 5V
- GND - GND

**LCD (ST7796S)**
- LCD_BL - 3.3V
- LCD_RST - GPIO 14
- LCD_DC - GPIO 27
- LCD_CS - GPIO 4
- SCKL - GPIO 18
- MOSI - GPIO 23
- GND - GND
- VCC - 5V

**PCM5102A**
- BCK - GPIO 12
- LCK - GPIO 33
- DIN - GPIO 32
- VCC - 5V
- GND - GND

**Buttons**
- Previous Song - 16
- Play/Pause - 17
- Stop - 21
- Next Song - 22


## 📖 How to Use
1. Insert `.wav` files into your SD card (16-bit PCM, 44.1kHz).
2. Connect all components as shown in the diagram.
3. Flash `src/main.ino` to your ESP32 board.
4. Use the buttons or touchscreen to control playback.

## 📸 Demo
[https://youtube.com/shorts/073RuDuK8ok?feature=share](https://youtube.com/shorts/073RuDuK8ok?feature=share)

---

## 💬 Notes & Acknowledgements

All planning, system design, and implementation logic were fully developed by me.

However, I received support from Chat4o during development — especially in:

- Recommending minimal required libraries for hardware modules
- Suggesting reliable initialization sequences for SPI (ST7796), I2S (PCM5102), and SD card
- Providing debugging tips

All code was written and tested by me, but I referred to ChatGPT for architectural validation and quick technical feedback when needed.

---

## 🎵 Music Credits
Music: Jazzy Night by Audio Library Beats Group
Free Download / Stream: [https://www.audiolibrary.com.co/audio-library-beats/jazzy-night](https://www.audiolibrary.com.co/audio-library-beats/jazzy-night)
Music promoted by Audio Library: [https://youtu.be/GNV-X6h9Hec](https://youtu.be/GNV-X6h9Hec)


Music: chimes by Snoozy Beats [https://soundcloud.com/snoozybeats](https://soundcloud.com/snoozybeats)
License: Creative Commons — Attribution 3.0 Unported — CC BY 3.0
Free Download / Stream: [https://www.audiolibrary.com.co/snoozybeats/chimes](https://www.audiolibrary.com.co/snoozybeats/chimes)
Music promoted by Audio Library: [https://youtu.be/9emPKhTjPVM](https://youtu.be/9emPKhTjPVM)


Music: Vortex by Declan DP
License: https://license.declandp.info
Free Download / Stream: [https://www.audiolibrary.com.co/declan-dp/vortex](https://www.audiolibrary.com.co/declan-dp/vortex)
Music promoted by Audio Library: [https://youtu.be/dkpo2ns1wqU](https://youtu.be/dkpo2ns1wqU)

---

Feel free to fork and modify. Built with love and curiosity. 🎧
