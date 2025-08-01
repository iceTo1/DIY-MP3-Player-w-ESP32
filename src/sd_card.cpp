#include "include/sd_card.h"
#include "include/utils.h"
#include <SD.h> // Library for SD card operations

#define SD_CS_PIN  5
 
// Flag for SD init
static bool sd_initialized = false;

// External variable for opened filename
String currentFileName;
int currentTrackIdx = 0;
std::vector<String> songList;

// Check if the SD card is initialized
bool sdCardInit()
{
    // If SD CS is not initialized
    if (!SD.begin(SD_CS_PIN))
    {
        // Print log, update flag, return false.
        Serial.println("SD Card Initialization Failed.");
        sd_initialized = false;
        return false;
    }

    // Print success log, update flag, return true.
    Serial.println("SD Card Initialized Successfully.");
    sd_initialized = true;
    return true;
}

// Show files in the SD cards
void listFiles(String path)
{
    // Reset the list vector
    songList.clear();

    // Check SD Card initialization
    if (!sd_initialized)
    {
        Serial.println("SD Not Initialized.");
        return;
    }

    // Adjust the path to begin with "/"
    path = adjustFileName(path);

    // Pass path with c string
    File root = SD.open(path.c_str());
    if (!root)
    {
        Serial.println("Failed to open root directory.");
        return;
    }

    // Check path validity
    if (!root.isDirectory())
    {
        Serial.println("Invalid Directory.");
        return;
    }

    // Open the first file
    Serial.println("Files: ");
    File file = root.openNextFile();

    // Until eof
    while (file)
    {
        // Store filename
        String name = String(file.name());
        Serial.print(" ");
        Serial.print(file.name());
        if (file.isDirectory())
        {
            Serial.println("/");
        }
        else
        {
            songList.push_back(name);
            Serial.print("\t");
            Serial.print(file.size());
            Serial.println(" bytes");
        }

        file = root.openNextFile();
    }

    // If file is empty
    if (songList.empty())
    {
        Serial.println("No playable file found.");
        currentFileName = "";
    }
    else
    {
        currentFileName = songList[0];
        Serial.printf("First song = %s\n", currentFileName.c_str());
    }
    
}

bool fileExists(String fileName)
{
    // Check SD Card initialization
    if (!sd_initialized)
    {
        return false;
    }

    // Adjust the filename
    fileName = adjustFileName(fileName);

    return SD.exists(fileName.c_str());
}