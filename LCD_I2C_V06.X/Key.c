
#include <pic.h>
#include "Key.h"

#define DEBOUNCE_MS 10
#define SHORT_PRESS_MS 20
#define LONG_PRESS_MS 300
#define LONG_PRESS_100MS 40
#define SCAN_INTERVAL 10 // 單位：ms，每次 KEY_Scan 呼叫間隔

KEY_T key[KEY_NUM];
uint8_t KeyState[KEY_NUM]; // 0: 按下，1: 放開

uint16_t ShortKey_cnt=0;
double LongKey_cnt=0;

void KEY_Init(void) {
  for (uint8_t i = 0; i < KEY_NUM; i++) {
    key[i].state = KEY_IDLE;
    key[i].press_time_ms = 0;
    key[i].release_time_ms = 0;
    key[i].fLong = 0;
    key[i].fLong_100ms = 0;
    key[i].fShort = 0;
    key[i].fKeyIn = 0;
  }
}

// 執行時間 320us
void KEY_ScanAll(void) {
  for (uint8_t ii = 0; ii < KEY_NUM; ii++) {
    KEY_T *k = &key[ii];

    switch (k->state) {
    case KEY_IDLE:
      // k->release_time_ms = 0;
      k->press_long_time_ms=0;
      k->press_time_ms = 0;
    //   if (k->fKeyIn == KEY_PRESS) { // 偵測按下
    //     k->state = KEY_DEBOUNCE;
    //   }
    //   break;

    // case KEY_DEBOUNCE:
      if (k->fKeyIn == KEY_PRESS) {
        // k->press_time_ms += SCAN_INTERVAL;
        // if (k->press_time_ms >= DEBOUNCE_MS) {
          // k->press_time_ms = 0;
          k->state = KEY_PRESSED;
        }
      // } else {
      //   k->state = KEY_IDLE;
      // }
      break;

    case KEY_PRESSED:
      if (k->fKeyIn == KEY_PRESS) {
        k->press_time_ms += SCAN_INTERVAL;
        if (k->press_time_ms >= LONG_PRESS_MS) {
          k->fLong = 1; //只會設定一次
          k->press_long_time_ms = 0;
          k->state = KEY_LONG;
        }
      } else { // 釋放
        k->release_time_ms = 0;//清空釋放計時器
        k->state = KEY_RELEASE;
      }
      break;

    case KEY_LONG:
      if (k->fKeyIn == KEY_PRESS) {
        k->press_long_time_ms += SCAN_INTERVAL;
        if (k->press_long_time_ms >= LONG_PRESS_100MS) {
          k->press_long_time_ms = 0;
          k->fLong_100ms = 1;
        }
      } else {
        k->press_time_ms=0; //長按 清空按鍵計時器
        k->release_time_ms = 0;//清空釋放計時器
        k->state = KEY_RELEASE;
      }
      break;

    case KEY_RELEASE:
      k->release_time_ms += SCAN_INTERVAL;
      if (k->release_time_ms >= DEBOUNCE_MS) { // 釋放防彈跳
        if (k->press_time_ms >= SHORT_PRESS_MS &&
            k->press_time_ms < LONG_PRESS_MS) {
              k->fShort = 1; //只會設定一次
              k->state = KEY_SHORT;
            } else {
              k->state = KEY_IDLE;
              k->fLong = 0;
            }
          }
          break;
          
    case KEY_SHORT:
      k->state = KEY_IDLE;
      break;

    default:
      break;
    }
  }
}
