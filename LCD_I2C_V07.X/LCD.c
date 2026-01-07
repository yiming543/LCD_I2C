/*
 * File:   LCD.c
 * Author: T00904
 *
 * Created on 2026年1月5日, 下午 3:48
 */

#include "LCD.h"
#include "RelayControl.h"
#include "TimerEven.h"
#include <xc.h>

uint8_t Cur_X = 0;
uint8_t Cur_Y = 0;
uint8_t LCD_X = 0;
uint8_t LCD_Y = 0;

void LCD_Init(void) {
  __delay_ms(50); // LCD啟動等待
  PCF8574_LCD_SendNibble(0x03, LCD_CMD);
  __delay_ms(5);
  PCF8574_LCD_SendNibble(0x03, LCD_CMD);
  __delay_ms(5);
  PCF8574_LCD_SendNibble(0x03, LCD_CMD);
  __delay_ms(5);

  PCF8574_LCD_SendNibble(0x02, LCD_CMD); // 進入4位元模式
  __delay_ms(1);

  LCD_Command(0x28); // 4-bit, 2 lines, 5x8 dots
                     // LCD_functionSet();      // 4-bit, 2 lines, 5x8 dots
                     // LCD_Command(DISP_ON_CUR_OFF); // Display ON, Cursor OFF
  // LCD_Command(DISP_ON_CUR_ON); // Display ON, Cursor OFF
  LCD_Command(DISP_ON_CUR_ON_BLOCK); // Display ON, Cursor OFF
  LCD_Command(0x06); // Entry mode
  LCD_Command(CLEAR_DISPLAY);
  __delay_ms(2);
}

void PWR_ON_DISP(void) {
  // 開機LCD顯示
  LCD_SetCursor(0, 0); // 第一行第一格
  sprintf(buf, "Welcome to LFA. ");
  LCD_Print(buf);

  LCD_SetCursor(0, 1); // 第二行第一格
  sprintf(buf, "Lamp test tool. ");
  LCD_Print(buf);
  __delay_ms(1000);

  LCD_SetCursor(0, 0); // 第一行第一格
  sprintf(buf, "Edit:EE Yiming  ");
  LCD_Print(buf);

  LCD_SetCursor(0, 1); // 第二行第一格
  sprintf(buf, "Version: 0.70   ");
  LCD_Print(buf);

  LCD_SetCursor(11, 1); // 第1行
  __delay_ms(1000);
}

void DISP_SHOW(void) {
  if (fLCD_updata) {
    fLCD_updata = 0;
    // TimeRestart();

    switch (LCD_DispMode) {
    case eNormal:
      LCD_Command(CLEAR_DISPLAY);
      LCD_SetCursor(0, 0); // 第1行
      DispNormal(_T1_, SetTimer1_ON_cnt, SET1_Timer, buf);
      LCD_Print(buf);

      LCD_SetCursor(0, 1); // 第2行第
      DispNormal(_T2_, SetTimer1_OFF_cnt, SET2_Timer, buf);
      LCD_Print(buf);
      // LCD_SetCursor(14, 1); // 第2行第
      LCD_SetCursor(11, 1); // 第1行
      break;

    case eTimeSetting1:
    case eTimeSetting2:
      LCD_SetCursor(3, Cur_Y);

      sprintf(buf, "%03d", tempTime_cnt);
      LCD_Print(buf);

      LCD_SetCursor(Cur_X, Cur_Y);
      break;

    case eTimerCount:
      LCD_SetCursor(7, 0);
      sprintf(buf, "%03d", SET1_Timer);
      LCD_Print(buf);

      LCD_SetCursor(7, 1);
      sprintf(buf, "%03d", SET2_Timer);
      LCD_Print(buf);

      if (SET1_TimerState == TIMER1_ON) {
        Cur_Y = 0;
        Cur_X = 9;
      } else {
        Cur_Y = 1;
        Cur_X = 9;
      }
      LCD_SetCursor(Cur_X, Cur_Y);
      break;

    default:
      break;
    }
  }
}