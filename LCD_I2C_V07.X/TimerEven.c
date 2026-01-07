// #include "mcc_generated_files/mcc.h"
#include "TimerEven.h"
#include "RelayControl.h"
#include "mcc_generated_files/pin_manager.h"
// #include "mcc_generated_files/pin_manager.h"
#include <stdbool.h>

bool fT0_10ms = 0;
bool fT1_1S = 0;

uint8_t T1_1000ms_cnt = 0;
uint16_t SET1_Timer = 0; // 第一組計時器
uint16_t SET2_Timer = 0; // 第二組計時器
uint16_t T_1S_cnt = 0; // 計時器 秒
#define T_1000MS 100     // 100 X 10MS

// 按鍵更新用
void TMR0_10msEven(void) { fT0_10ms = 1; }

// Relay計時用 11.6us
void TMR1_10msEven(void) {
  if (!OutState) {
    T1_1000ms_cnt = 0;
    fT1_1S = 0;
  } else {
    T1_1000ms_cnt++;

    if (T1_1000ms_cnt >= T_1000MS) {
      T1_1000ms_cnt = 0;
      T_1S_cnt++;
      fT1_1S = 1;
      fLCD_updata = 1;
      KeepTimerCounter();
    }
  }
}