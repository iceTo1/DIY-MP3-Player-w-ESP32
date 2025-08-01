#include "include/config.h"
#include "include/buttons.h"
#include "include/sd_card.h"
#include "include/audio.h"
#include "include/lcd.h"
#include <Arduino.h>

unsigned long lastStop = 0;
unsigned long lastNext = 0;
unsigned long lastPrev = 0;
const unsigned long dbTime = 50;

bool prevPlayPause = HIGH;
bool prevNext = HIGH;
bool prevPrev = HIGH;
bool prevStop = HIGH;

bool isPlaying = false;
bool isPaused = true;

ButtonEvent detectButtonEvent()
{
  // Read button state
  bool currPlayPause = digitalRead(PLAY_PAUSE_BUTTON);
  bool currNext      = digitalRead(NEXT_SONG_BUTTON);
  bool currPrev      = digitalRead(PREV_SONG_BUTTON);
  bool currStop      = digitalRead(STOP_BUTTON);

  ButtonEvent event = BTN_NONE;

  // Check if pressed
  if (currPlayPause != prevPlayPause && currPlayPause == LOW)
  {
    event = BTN_PLAY;
  }
  else if (currNext != prevNext && currNext == LOW)
  {c:\Users\leest\Desktop\FUN\ESP Player\esp_player\include\utils.h
    event = BTN_NEXT;
  }
  else if (currPrev != prevPrev && currPrev == LOW)
  {
    event = BTN_PREV;
  }
  else if (currStop != prevStop && currStop == LOW) 
  {
    event = BTN_STOP;
  }

  // Update state
  prevPlayPause = currPlayPause;
  prevNext      = currNext;
  prevPrev      = currPrev;
  prevStop      = currStop;

  // Return detected event
  return event;
}
