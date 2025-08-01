#include "include/audio.h"
#include "include/config.h"
#include "include/utils.h"
#include "include/buttons.h"
#include "driver/i2s.h"
#include <SD.h>

#define SAMPLE_RATE 44100

File currentFile;
// bool isPlaying = false;
// bool isPaused = true;

bool audioInit()
{
  // PCM module settings: 44100Hz, 16bit, stereo, with I2S_MSB
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S_MSB,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 12,
    .dma_buf_len = 512,
    .use_apll = true,
    .tx_desc_auto_clear = true,
    .fixed_mclk = 0
  };

  // Init pins
  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_BCK,
    .ws_io_num = I2S_WS,
    .data_out_num = I2S_DATA,
    .data_in_num = I2S_PIN_NO_CHANGE
  };

  // Initialize I2S
  esp_err_t err;
  // Check i2s driver installation
  err = i2s_driver_install(I2S_NUM, &i2s_config, 0, NULL);
  Serial.printf("i2s_driver_install: %d\n", err);

  // Check i2s pin setting
  err = i2s_set_pin(I2S_NUM, &pin_config);
  Serial.printf("i2s_set_pin: %d\n", err);

  // Check?
  i2s_set_clk(I2S_NUM, SAMPLE_RATE, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_STEREO);

  // Run i2s
  err = i2s_start(I2S_NUM);
  Serial.printf("i2s_start: %d\n", err);

  return true;
}


// First Playing test, playout the whole file; cannot detect buttons
bool audioPlay(String fileName)
{

  fileName = adjustFileName(fileName);
  
  File file = SD.open(fileName.c_str());
  if (!file)
  {
    Serial.printf("Failed to open audio file: %s\n", fileName.c_str());
    return false;
  }

  // Skip WAV header (44 bytes)
  file.seek(44);

  uint16_t buffer[512];
  size_t bytes_read, bytes_written;

  Serial.println("Playing audio...");

  // Read from the file, steps of 512 bytes
  while ((bytes_read = file.read((uint8_t*)buffer, sizeof(buffer))) > 0)
  {
    i2s_write(I2S_NUM, buffer, bytes_read, &bytes_written, portMAX_DELAY);
    // Serial.printf("Written %d bytes (of %d)\n", bytes_written, bytes_read);
  }

  Serial.println("Playback Complete");
  file.close();

  return true;
}

bool audioPlay2(String fileName)
{
  fileName = adjustFileName(fileName);
  currentFile = SD.open(fileName.c_str());
  if (!currentFile)
  {
    Serial.printf("Failed to open audio file: %s\n", fileName.c_str());
    return false;
  }

  currentFile.seek(44);  // Skip WAV header
  isPlaying = true;
  isPaused = false;
  return true;
}

void audioPause()
{
  i2s_stop(I2S_NUM_0);
  isPaused = true;
}

void audioResume()
{
  i2s_start(I2S_NUM_0);
  isPaused = false;
}

void audioStop()
{
  isPlaying = false;
  isPaused = false;
  if (currentFile) currentFile.close();
  i2s_zero_dma_buffer(I2S_NUM);
}
