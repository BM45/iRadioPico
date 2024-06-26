#include "globals.h"
#include "lfs.h"

#include <Arduino.h>

#include "LittleFS.h"

int readWifiConfigLittleFS(){
   SERIAL_PORT.println("\nLITTLEFS: Initializing LittleFS...");
    
   if (!LittleFS.begin()){
     SERIAL_PORT.println(F("LITTLEFS: initialization failed!"));
     return LFS_FAILURE;
   }
   SERIAL_PORT.println("LITTLEFS: initialization done.");;
  
   File dir = LittleFS.open("/", "r");   
   if (LittleFS.exists("wifi.txt")) {
     SERIAL_PORT.println("LITTLEFS: wifi.txt exists.");
     File fd = LittleFS.open("wifi.txt","r");
     if (fd) {
	while (fd.available()) {
          String line = fd.readStringUntil('\n');  // \n character is discarded from buffer
     	  
     	  // SSID
     	  if ( line.indexOf("ssid=") != -1) {
     	     SERIAL_PORT.print("LITTLEFS: SSID found: ");
     	     String data = line.substring(line.indexOf("ssid=")+6,line.indexOf("\"", line.indexOf("ssid=")+6));
     	     memcpy(ssid,data.c_str(),data.length());
     	     SERIAL_PORT.println(ssid);
     	  }
     	  
     	  // PSK
     	  if ( line.indexOf("psk=") != -1) {
     	     SERIAL_PORT.print("LITTLEFS: PSK found: ");
     	     String data = line.substring(line.indexOf("psk=")+5,line.indexOf("\"", line.indexOf("psk=")+5));
     	     memcpy(password,data.c_str(),data.length());
     	     SERIAL_PORT.println(password);
     	  }
       } //  while (fd.available()) {
       fd.close();
     } // if (fd) {
   } else {
         SERIAL_PORT.println("LITTLEFS: wifi.txt doesn't exist.");
         return LFS_FAILURE_NO_FILE;
   }

  return LFS_OK;
}


int readPlaylistLittleFS() {      
  SERIAL_PORT.println("\nLITTLEFS: Initializing LittleFS...");
    
  if (!LittleFS.begin()){
      SERIAL_PORT.println(F("LITTLEFS: initialization failed!"));
      return LFS_FAILURE;
  }
  SERIAL_PORT.println("LITTLEFS: initialization done.");
         
  File dir = LittleFS.open("/", "r");   
  if (LittleFS.exists("/playlist.m3u")) {
    SERIAL_PORT.println("LITTLEFS: playlist exists.");
    File fd = LittleFS.open("playlist.m3u","r");
    if (fd) {
      unsigned int line_count = 0;
      while ((fd.available()) && (line_count < MAX_CHANNELS_IN_LIST)) {
        String url = fd.readStringUntil('\n');  // \n character is discarded from buffer
        if ((url.length()>0) && (url.length()<255)) {
          playlist[line_count]=(char*) malloc(255*sizeof(char));
          url.toCharArray(playlist[line_count], url.length()+1);
          line_count++;
        
          SERIAL_PORT.print("LITTLEFS: playlist at line ");
          SERIAL_PORT.print(line_count);
          SERIAL_PORT.print(" : ");
          SERIAL_PORT.println(url);
        } // if ((url.length()>0) && (url.length()<255)) {
      } // while ((fd.available()) && (line_count < MAX_CHANNELS_IN_LIST)) {
      channels_in_list = line_count;
      fd.close();
    } // if (fd) {
  } else {
    SERIAL_PORT.println("LITTLEFS: playlist doesn't exist.");
    return LFS_FAILURE_NO_FILE;
  }
  return LFS_OK;
} 


int writeRadioSettingsLittleFS() {
  SERIAL_PORT.println("\nLITTLEFS: Initializing LittleFS...");
    
  if (!LittleFS.begin()){
      SERIAL_PORT.println(F("LITTLEFS: initialization failed!"));
      return LFS_FAILURE;
  }
  SERIAL_PORT.println("LITTLEFS: initialization done.");
         
  File fd = LittleFS.open("/settings.txt", "w");
  if (!fd) {
    SERIAL_PORT.println("LITTLEFS: write radio settings to file failed");
    return LFS_FAILURE_NO_FILE;
  }
  
  fd.printf("actual_channel_or_file_ID=%i\n",actual_channel_or_file_ID);
  fd.printf("volume_L=%i\n",volume_L);
  fd.printf("volume_R=%i\n",volume_R);
  fd.printf("radiomode=%i\n",radiomode);

  fd.printf("alarm1_status=%i\n",alarm1_status);
  fd.printf("alarm1_year=%i\n",alarm1.year);
  fd.printf("alarm1_month=%i\n",alarm1.month);  
  fd.printf("alarm1_day=%i\n",alarm1.day);
  fd.printf("alarm1_dotw=%i\n",alarm1.dotw);
  
  fd.printf("alarm1_hour=%i\n",alarm1.hour);
  fd.printf("alarm1_min=%i\n",alarm1.min);
  fd.printf("alarm1_sec=%i\n",alarm1.sec);
    
  // { .year  = -1, .month = -1, .day   = -1, .dotw  = -1, .hour  = -1, .min   = -1, .sec   = -1  };
  
  fd.close();
  SERIAL_PORT.println("LITTLEFS: radio settings written to file");
  
  return LFS_OK;
}



int readRadioSettingsLittleFS() {
  SERIAL_PORT.println("\nLITTLEFS: Initializing LittleFS...");
    
  if (!LittleFS.begin()){
      SERIAL_PORT.println(F("LITTLEFS: initialization failed!"));
      return LFS_FAILURE;
  }
  SERIAL_PORT.println("LITTLEFS: initialization done.");
         
  File fd = LittleFS.open("/settings.txt", "r");
  if (!fd) {
    SERIAL_PORT.println("LITTLEFS: read radio settings from file failed");
    return LFS_FAILURE_NO_FILE;
  }
  
  while (fd.available()) {
     String line = fd.readStringUntil('\n');  // \n character is discarded from buffer
     SERIAL_PORT.println(line);
     SERIAL_PORT.flush();
     
     if ( line.indexOf("actual_channel_or_file_ID=") != -1) {
       String data = line.substring(line.indexOf("ID=")+3);
       actual_channel_or_file_ID = data.toInt();
     } 
     
     if ( line.indexOf("volume_L=") != -1) {
       String data = line.substring(line.indexOf("L=")+2);
       volume_L = data.toInt();
     } 
     
     if ( line.indexOf("volume_R=") != -1) {
       String data = line.substring(line.indexOf("R=")+2);
       volume_R = data.toInt();
     } 
     
     if ( line.indexOf("radiomode=") != -1) {
       String data = line.substring(line.indexOf("=")+1);
       radiomode = (RadioMode) data.toInt();
     } 
     
     if ( line.indexOf("alarm1_status=") != -1) {
       String data = line.substring(line.indexOf("=")+1);
       alarm1_status = (AlarmStatus) data.toInt();
     } 

     if ( line.indexOf("alarm1_year=") != -1) {
       String data = line.substring(line.indexOf("=")+1);
       alarm1.year = data.toInt();
     } 
     
     if ( line.indexOf("alarm1_month=") != -1) {
       String data = line.substring(line.indexOf("=")+1);
       alarm1.month = data.toInt();
     } 
  
     if ( line.indexOf("alarm1_day=") != -1) {
       String data = line.substring(line.indexOf("=")+1);
       alarm1.day = data.toInt();
     }    

     if ( line.indexOf("alarm1_dotw=") != -1) {
       String data = line.substring(line.indexOf("=")+1);
       alarm1.dotw = data.toInt();
     }    

     if ( line.indexOf("alarm1_hour=") != -1) {
       String data = line.substring(line.indexOf("=")+1);
       alarm1.hour = data.toInt();
     } 

     if ( line.indexOf("alarm1_min=") != -1) {
       String data = line.substring(line.indexOf("=")+1);
       alarm1.min = data.toInt();
     } 

     if ( line.indexOf("alarm1_sec=") != -1) {
       String data = line.substring(line.indexOf("=")+1);
       alarm1.sec = data.toInt();
     } 
     

  } //  while (fd.available()) {
  
  fd.close();
  SERIAL_PORT.println("LITTLEFS: radio settings imported from settings.txt");
  return LFS_OK;
}
