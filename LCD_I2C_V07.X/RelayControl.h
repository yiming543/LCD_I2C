#ifndef RELAYCONTROL_H
#define RELAYCONTROL_H

#include "LCD.h"
#include "mcc_generated_files/mcc.h"
#include <stdbool.h>


enum DISP_MODE {
  eNormal = 0,
  // eTimeSelect = 1,
  // eTimeSetting = 2,
  eTimeSetting1,
  eTimeSetting2,
  eTimerCount,
  // eTimeAdjustment = 4,
};

#define MAX_NUM 999
#define MIN_NUM 0

// #define LINE_MAX 3  //4行
#define LINE_MAX 1 // 2行
#define LINE_MIN 0

#define _T1_ 1
#define _T2_ 2
#define TIMER1_ON 0
#define TIMER1_OFF 1
#define ON 1
#define OFF 0
#define RELAY_ON Relay_en_LAT = ON;
#define RELAY_OFF Relay_en_LAT = OFF;

// extern
extern char buf[17];
extern uint16_t SetTimer1_ON_cnt;
extern uint16_t SetTimer1_OFF_cnt;
extern bool OutState;
extern bool SET1_TimerState;
extern bool SET1_RelayState;

extern uint8_t LCD_DispMode;

extern uint16_t tempTime_cnt;
extern uint8_t set_time;

bool fLCD_updata;
// bool fDOT;

void RelayControl_Init(void);
void Number2Digital(uint16_t Num, uint8_t *digital);
void Digital2Number(uint16_t *Num, uint8_t *digital);

void DispNormal(uint8_t n, uint16_t Num, uint16_t Num2, char *buf);
void TimeRestart(void);
void DispFunctionSet(uint8_t mode, uint8_t n, uint16_t Num, char *buf);
void DispTimeAdjustment(uint8_t mode, uint8_t n, uint16_t Num, char *buf);

void Normal(void);
void TimerCount(void);
void TimeSelect(void);
void TimeSetting(void);

void TimeSetting1(void);
void TimeSetting2(void);

uint16_t GetTimerN_Value(uint8_t x);
void SetTimerN_Value(uint8_t x);

// In T1_ISR
void KeepTimerCounter(void);

#endif /* RELAYCONTROL_H */