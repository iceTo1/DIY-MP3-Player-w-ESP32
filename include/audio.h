#ifndef AUDIO_H
#define AUDIO_H

#include <Arduino.h>
#include <SD.h>

bool audioInit();
void audioTest();
void playNote(float freq, int durationMs);
bool audioPlay(String fileName);
bool audioPlay2(String fileName);
void audioPause();
void audioResume();
void audioStop();

extern File currentFile;

#endif
