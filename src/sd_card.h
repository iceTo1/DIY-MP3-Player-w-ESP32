#ifndef SD_CARD_H
#define SD_CARD_H

#include <Arduino.h>

extern String currentFileName;       // filename
extern std::vector<String> songList; // song list
extern int currentTrackIdx;          // list index

bool sdCardInit();
void listFiles(String path);
bool fileExists(String fileName);

#endif