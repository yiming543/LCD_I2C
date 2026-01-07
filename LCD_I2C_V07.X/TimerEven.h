#ifndef TIMER_EVEN_H
#define TIMER_EVEN_H
// #include "mcc_generated_files/mcc.h"
#include <stdbool.h>
#include <stdint.h>

extern void TMR0_10msEven(void);
extern void TMR1_10msEven(void);

extern bool fT0_10ms;
extern bool fT0_1second;

extern bool fT1_10ms;
extern bool fT1_100ms;
extern bool fT1_1S;

// extern uint16_t x1T_cnt;
// extern uint16_t x10T_cnt;
// extern uint16_t x100T_cnt;
extern uint16_t SET1_Timer;
extern uint16_t SET2_Timer;

// extern uint16_t T1_10ms_cnt;
// extern uint16_t T1_100ms_cnt;
extern uint8_t T1_1000ms_cnt;

extern uint16_t T_1S_cnt; // 計時器 秒

#endif /* TIMER_EVEN_H */