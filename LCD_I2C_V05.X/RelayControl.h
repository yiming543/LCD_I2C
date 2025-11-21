#ifndef RELAYCONTROL_H
#define RELAYCONTROL_H

#include "mcc_generated_files/mcc.h"
#include <stdbool.h>

enum DISP_MODE {
  eNormal = 0,
  eFunctionSet = 1,
  eTimeAdjustment = 2,
};

enum TIME_UNIT {
  e1_000S = 1,
  e0_100S = 2,
  e0_010S = 3,
  //   e0_001S = 4,
}; // 1~9999.S   0.100~999.9   0.010~99.99   0.001~9.999

enum ADJUST_T1 {
  eADJ_T1_DIG1 = 1,
  eADJ_T1_DIG2 = 2,
  eADJ_T1_DIG3 = 3,
  eADJ_T1_DIG4 = 4,
  eADJ_T2_DIG1 = 5,
  eADJ_T2_DIG2 = 6,
  eADJ_T2_DIG3 = 7,
  eADJ_T2_DIG4 = 8,
};

#define MAX_NUM 9
#define MIN_NUM 0

#define _T1_ 1
#define _T2_ 2
#define TIMER1 0
#define TIMER2 1
#define ON 1
#define OFF 0
#define RELAY_ON Relay_en_LAT = ON;
#define RELAY_OFF Relay_en_LAT = OFF;

// extern
extern uint8_t TimeMode;
extern uint8_t AdjustMode;
extern uint8_t Cursor_pos;

extern char buf[17];
extern uint16_t SetTimer1_cnt;
extern uint16_t SetTimer2_cnt;
extern bool OutState;
extern bool TimerState;
// extern bool fFunctionSet;
extern uint8_t LCD_DispMode;
bool fLCD_updata;

void RelayControl_Init(void);
void Number2Digital(uint16_t Num, uint8_t *digital);
void Digital2Number(uint16_t *Num, uint8_t *digital);

void DispNormal(uint8_t mode, uint8_t n, uint16_t Num, char *buf);
void TimeModeSelect(void);
void DispFunctionSet(uint8_t mode, uint8_t n, uint16_t Num, char *buf);
void DispTimeAdjustment(uint8_t mode, uint8_t n, uint16_t Num, char *buf);

void Normal(void);
void FunctionSet(void);
void TimeAdjustment(void);

// In T1_ISR
void KeepTimerCounter(void);

#endif /* RELAYCONTROL_H */