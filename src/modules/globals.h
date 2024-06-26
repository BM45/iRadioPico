#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#define SERIAL_PORT Serial

#define USE_NTP_CLOCK_SYNC

#define USE_WATCHDOG

//#define USE_SDCARD
#define USE_LITTLEFS

// AUTO_SAVE only on LitteFS at the moment, so USE_LITTLEFS must be set
#define USE_AUTO_SAVE

//#define USE_ETHERNET 
//#define USE_ENC28J60
//#define USE_W5100
//#define USE_W5500

#ifdef USE_ETHERNET
    #define SPI_PIN_RX  0
    #define SPI_PIN_CS  1
    #define SPI_PIN_SCK 2
    #define SPI_PIN_TX  3
#endif

#define USE_WIFI


#define USE_VS1053_DECODER
//#define USE_INTERNAL_CODEC_WITH_CUSTOM_LIB

// wiring VS1053-DSP
#define VS1053_CS     15   // VS1053 Chip Select Pin
#define VS1053_DCS     14   // VS1053 Data/Command Select Pin
#define VS1053_DREQ    13  // VS1053 Data request
#define VS1053_MOSI    12  // VS1053 MOSI
#define VS1053_MISO    11  // VS1053 MISO
#define VS1053_CLK     10   // VS1053 Clock Pin
#define VS1053_RESET   9   // VS1053 reset pin (-1 unbelegt)

//#define USE_INTERNAL_VU_METER
#define USE_VLSI_VSDSP_VU_METER

// set by wifi.txt, playlist.m3u and settings.txt from SDCARD/LFS
#define MAX_CHANNELS_IN_LIST 100
extern char* playlist[MAX_CHANNELS_IN_LIST];
extern unsigned int channels_in_list;
extern unsigned int actual_channel_or_file_ID;

extern char ssid[32];           
extern char password[64];

extern unsigned int volume_L, volume_R;


enum RadioMode { STANDBY, INTERNETRADIO, FMTUNER };
extern RadioMode radiomode;


#include "hardware/rtc.h"

enum AlarmStatus { ALARM_DISABLED, ALARM_ENABLED };
extern AlarmStatus alarm1_status;
extern datetime_t alarm1; // { .year  = -1, .month = -1, .day   = -1, .dotw  = -1, .hour  = -1, .min   = -1, .sec   = -1  };

#endif
