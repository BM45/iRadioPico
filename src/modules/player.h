#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Arduino.h"

enum Player_State { STOPPED,   PREPARING,   RUNNING ,  PAUSED,	PREPAIRING_FAILED };
enum Player_Event { NO_EVENT, VOLUME_CHANGED };

struct PlayerInfo {           
  unsigned int cur_ch_no;        
  char* cur_url_playing;
  int cur_buffer_level;
  Player_State cur_player_state;
  int cur_HTTP_RESPONSE = 0;
  uint16_t pcm_value_left, pcm_value_right;
  
  #ifdef USE_VLSI_VSDSP_VU_METER
  	 uint8_t vsdsp_vu_left, vsdsp_vu_right;
  #endif
};  
 
void player_init();
void player_run();

void goto_station(int);
void next_station();
void prev_station();
void pause_player();
void resume_player();
void stop_player();
void start_player();
void volume_up();
void volume_down();


PlayerInfo getPlayerInfo(void);

#endif
