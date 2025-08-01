#ifndef BUTTONS_H
#define BUTTONS_H

#include "include/config.h"

enum ButtonEvent {
  BTN_NONE,
  BTN_PLAY,
  BTN_PAUSE,
  BTN_NEXT,
  BTN_PREV,
  BTN_STOP
};

ButtonEvent detectButtonEvent();

extern bool isPlaying;
extern bool isPaused;
extern unsigned long lastStop;
extern unsigned long lastNext;
extern unsigned long lastPrev;
extern const unsigned long dbTime;

extern bool isPlaying;
extern bool isPaused;

extern ButtonEvent event;


#endif