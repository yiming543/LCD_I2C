// #include "mcc_generated_files/mcc.h"
#include "TimerEven.h"
#include "RelayControl.h"
#include "mcc_generated_files/pin_manager.h"
// #include "mcc_generated_files/pin_manager.h"
#include <stdbool.h>

static uint8_t T0_10ms_cnt = 0;
bool fT0_fT10ms = 0;
bool fT0_1second = 0;
static uint8_t T0_1second_cnt = 0;
bool fT1_10ms = 0;
bool fT1_100ms = 0;
bool fT1_1second = 0;
bool fT1_TimerUp = 0;

uint16_t T1_10ms_cnt = 0;
uint16_t T1_100ms_cnt = 0;
uint16_t T1_1000ms_cnt = 0;

uint16_t x1T_cnt = 0;
uint16_t x10T_cnt = 0;
uint16_t x100T_cnt = 0;
uint16_t xComm_cnt = 0;
#define x10T 10
#define x100T 100

// 按鍵更新用
void TMR0_10msEven(void) {
  T0_10ms_cnt++;
  fT0_fT10ms = 1;
  T0_1second_cnt++;
  if (T0_1second_cnt >= 50) {
    T0_1second_cnt = 0;
    fT0_1second = 1;
  }
}

// Relay計時用 11.6us
void TMR1_10msEven(void) {
  T1_10ms_cnt++;
  T1_100ms_cnt++;
  T1_1000ms_cnt++;

  x1T_cnt++;
  fT1_10ms = 1;
  if (TimeMode == e0_010S) {
    fT1_TimerUp = 1;
    xComm_cnt = x1T_cnt;
  }

  if (T1_100ms_cnt >= x10T) {
    T1_100ms_cnt = 0;
    x10T_cnt++;
    fT1_100ms = 1;
    if (TimeMode == e0_100S) {
      fT1_TimerUp = 1;
      xComm_cnt = x10T_cnt;
    }
  }

  if (T1_1000ms_cnt >= x100T) {
    T1_1000ms_cnt = 0;
    x100T_cnt++;
    fT1_1second = 1;
    if (TimeMode == e1_000S) {
      fT1_TimerUp = 1;
      xComm_cnt = x100T_cnt;
    }
  }
  
  KeepTimerCounter();
}