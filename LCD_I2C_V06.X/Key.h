#ifndef KEY_H
#define KEY_H

#include <stdbool.h>
#include <stdint.h>


#define KEY_NUM 4
#define KEY_PRESS 1

#define KEY_UP_S key[0].fShort 
#define KEY_SELECT_S key[1].fShort 
#define KEY_DOWN_S key[2].fShort 
#define KEY_OUT_S key[3].fShort 

#define KEY_UP_L key[0].fLong 
#define KEY_SELECT_L key[1].fLong 
#define KEY_DOWN_L key[2].fLong 
#define KEY_OUT_L key[3].fLong 

#define KEY_UP_L_100sm key[0].fLong_100ms 
#define KEY_DOWN_L_100ms key[2].fLong_100ms

// 按鍵狀態
typedef enum {
  KEY_IDLE = 0,
  KEY_DEBOUNCE,
  KEY_PRESSED,
  KEY_SHORT,
  KEY_LONG,
  KEY_RELEASE
} KEY_STATE_E;

// 按鍵結構
typedef struct {
  KEY_STATE_E state;
  uint16_t press_time_ms;      // 持續按下時間
  uint16_t press_long_time_ms; // key long成立後持續按下時間
  uint16_t release_time_ms;    // 按下後放開時間
  uint8_t fLong;               // 長按事件標誌
  uint8_t fLong_100ms;         // 長按事件_100ms標誌
  uint8_t fShort;              // 短按事件標誌
  uint8_t fKeyIn;               // 按鍵狀態
} KEY_T;

extern KEY_T key[KEY_NUM];
extern uint8_t KeyState[KEY_NUM];
extern uint16_t ShortKey_cnt;
extern double LongKey_cnt;

// void KEY_ScanAll(uint8_t *key_level, KEY_T *key);
void KEY_ScanAll(void);
void KEY_Init(void);

#endif /* KEY_H */