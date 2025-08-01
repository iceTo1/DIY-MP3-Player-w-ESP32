#include <Arduino.h>
#include "include/config.h"
#include "include/audio.h"
#include "include/sd_card.h"
#include "include/lcd.h"
#include "include/buttons.h"
#include "driver/i2s.h"

static bool firstPlay;

void setup()
{
  Serial.begin(115200);
  delay(1000);

  pinMode(STOP_BUTTON,  INPUT_PULLUP);
  pinMode(NEXT_SONG_BUTTON,  INPUT_PULLUP);
  pinMode(PLAY_PAUSE_BUTTON, INPUT_PULLUP);
  pinMode(PREV_SONG_BUTTON,  INPUT_PULLUP);

  lcd.init();

  // SD Card Init Tests
  if (!sdCardInit())
  {
    Serial.println("SD card init failed");
    return;
  }
  else
  {
    listFiles("/");
  }

  // Audio Init Tests
  if (!audioInit())
  {
    Serial.println("Audio init failed");
    return;
  }

  Serial.println("SETUP DONE");

  // Show boot screen
  lcd.fillScreen(BLACK);

  lcd.drawStringCentered("ST's DIY", 320, 150, GREEN, 4);
  lcd.drawStringCentered("MP3 Player", 320, 350, GREEN, 4);
  lcd.drawStringCentered("Press any button to play", 320, 700, WHITE, 2.25);

  // LCD: Navy
  Serial.println("Waiting for button to be pressed...");
  while (digitalRead(STOP_BUTTON) == HIGH && digitalRead(NEXT_SONG_BUTTON) == HIGH 
      && digitalRead(PLAY_PAUSE_BUTTON) == HIGH && digitalRead(PREV_SONG_BUTTON) == HIGH)
  {
    // Standby
    firstPlay = true;
    delay(10);
  }

  lcd.fillScreen(NAVY);
  Serial.println("Button pressed, proceeding...");
  delay(200);
}

void loop()
{
  if (firstPlay)
  {
    isPlaying = true;
    isPaused = false;
    currentFileName = songList[currentTrackIdx];
    audioPlay2(currentFileName);
    lcd.drawPlayingState("Playing", currentFileName);
    firstPlay = false;
  }

  ButtonEvent eventStatus = detectButtonEvent();

  if (eventStatus != BTN_NONE)
  {
    switch (eventStatus)
    {
    case BTN_PLAY:
    if (isPlaying && !isPaused)
    {
      audioPause();
      // isPaused = true;
      lcd.drawPlayingState("Paused", currentFileName);
    }
    else if (isPlaying && isPaused)
    {
      audioResume();
      // isPaused = false;
      lcd.drawPlayingState("Playing", currentFileName);
    }
    else
    {
      currentFileName = songList[currentTrackIdx];
      isPlaying = true;
      isPaused = false;
      audioPlay2(currentFileName);
      lcd.drawPlayingState("Playing", currentFileName);
    }
    break;
    
    case BTN_STOP:
      audioStop();
      lcd.drawPlayingState("Stopped", currentFileName);
      break;

    case BTN_NEXT:
      // Modulus operation to circulate list
      currentTrackIdx = (currentTrackIdx + 1) % songList.size();
      currentFileName = songList[currentTrackIdx];
      audioPlay2(currentFileName);
      // isPlaying = true;
      // isPaused = false;
      lcd.drawPlayingState("Playing", songList[currentTrackIdx]);
      break;
    
    case BTN_PREV:
      currentTrackIdx = (currentTrackIdx - 1 + songList.size()) % songList.size();
      currentFileName = songList[currentTrackIdx];
      audioPlay2(currentFileName);
      isPlaying = true;
      isPaused = false;
      lcd.drawPlayingState("Playing", songList[currentTrackIdx]);
      break;
    }
  }

  if (isPlaying && !isPaused && currentFile)
  {
    static uint8_t buffer[512];
    if (currentFile.available())
    {
      size_t bytes_read = currentFile.read(buffer, sizeof(buffer));
      size_t bytes_written;
      i2s_write(I2S_NUM, buffer, bytes_read, &bytes_written, 100);  // 100ms timeout
    }
    else
    {
      Serial.println("Playback complete");
      currentFile.close();
      isPlaying = false;
    }
  }
}

  Buttons();
}
*/
