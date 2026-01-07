#include "RelayControl.h"
#include "Key.h"
#include "TimerEven.h"
#include "eeprom.h"
#include "hd44780_i2c.h"
#include <string.h>

char buf[17] = {0};
uint16_t SetTimer1_ON_cnt = 0;
uint16_t SetTimer1_OFF_cnt = 0;

uint16_t tempTime_cnt = 0;
uint8_t set_time = 0;

bool OutState = OFF; // 輸出狀態
char RelayState_buf[3] = {0};

bool SET1_TimerState = TIMER1_ON; // 0:TIMER1_ON 1:TIMER1_OFF
bool SET1_RelayState = OFF;       // 繼電器 狀態

uint8_t LCD_DispMode = 0;
bool fLCD_updata = 0; // 更新LCD旗標

void RelayControl_Init(void) {
  RELAY_OFF;
  SET1_RelayState = OFF;
  LCD_DispMode = eNormal;
  fLCD_updata = 1;
}

void TimeRestart(void) {
  T1_1000ms_cnt = 0;
  SET1_Timer = 0;
  SET2_Timer = 0;
  fT1_1S = 0;
}

// void Number2Digital(uint16_t Num, uint8_t *digital1, uint8_t *digital2,
// uint8_t *digital3, uint8_t *digital4) {
// void Number2Digital(uint16_t Num, uint8_t *digiNum) {
//   uint16_t temp = 0;
//   temp = Num / 1000;
//   digiNum[0] = (uint8_t)temp;
//   Num = Num - (temp * 1000); // new Num

//   temp = Num / 100;
//   digiNum[1] = (uint8_t)temp;

//   Num = Num - (temp * 100); // new Num

//   temp = Num / 10;
//   digiNum[2] = (uint8_t)temp;

//   digiNum[3] = (uint8_t)(Num % 10);
// }

// void Digital2Number(uint16_t *Num, uint8_t *digital) {
//   uint16_t temp1 = (uint16_t)digital[0];
//   uint16_t temp2 = (uint16_t)digital[1];
//   uint16_t temp3 = (uint16_t)digital[2];
//   uint16_t temp4 = (uint16_t)digital[3];

//   *Num = temp1 * 1000 + temp2 * 100 + temp3 * 10 + temp4;
// }

void DispNormal(uint8_t n, uint16_t Num, uint16_t Num2, char *buf) {
  char temp_str[4] = {0};
  char temp_state[3] = {0};

  // 第1行顯示OUT ON/OFF，第2行空白
  if (n == _T1_) {
    strncpy(temp_state, "ON", 2);
    strncpy(temp_str, "   ", 3);
    // if (OutState)
    //   strncpy(temp_str, "ON ", 3);
    // else
    //   strncpy(temp_str, "OFF", 3);

  } else {
    strncpy(temp_state, "OF", 2);
    strncpy(temp_str, "   ", 3);
  }

  sprintf(buf, "%s:%03d %03d %s", temp_state, Num, Num2, temp_str);
}

void KeepTimerCounter(void) {
  if (OutState == OFF || SetTimer1_ON_cnt == 0) {
    // Relay off
    RELAY_OFF;
  } else {
    // 計時中
    if (fT1_1S) {
      fT1_1S = 0;
      // TIMER1_ON
      if (SetTimer1_ON_cnt > 0) {
        if (SET1_TimerState == TIMER1_ON) {
          SET1_Timer = T_1S_cnt;
          if (T_1S_cnt >= SetTimer1_ON_cnt) {
            T_1S_cnt = 0;
            SET2_Timer=0;
            //不OFF一直ON
            if(SetTimer1_OFF_cnt >0){
              RELAY_OFF;
              SET1_RelayState = OFF;
              SET1_TimerState = TIMER1_OFF;
            }
          }
        } else { // TIMER1_OFF
          SET2_Timer = T_1S_cnt;
          if (T_1S_cnt >= SetTimer1_OFF_cnt) {
            T_1S_cnt = 0;
            SET1_Timer=0;
            RELAY_ON;
            SET1_RelayState = ON;
            SET1_TimerState = TIMER1_ON;
          }
        }
      } else {
        // Relay off
        RELAY_OFF;
      }
    }
  }
}

void Normal(void) {
  // 只接收2個功能
  // 1.SW2長按 進入設定時間模式
  // 2.SW4短按 Relay ON 開始計時

  // FunctionSet
  if (KEY_SELECT_L) {
    KEY_SELECT_L = 0;
    KEY_SELECT_S =0;
    KEY_UP_S=0;
    KEY_UP_L=0;
    KEY_UP_L_100sm=0;
    KEY_DOWN_S=0;
    KEY_DOWN_L=0;
    KEY_DOWN_L_100ms=0;
    KEY_OUT_S=0;

    fLCD_updata = 1;
    // LCD_DispMode = eFunctionSet;
    LCD_DispMode = eTimeSetting1;
    OutState = OFF;
    RELAY_OFF;
    short_led_Toggle();
    set_time = 0;
    tempTime_cnt = GetTimerN_Value(set_time);
    Cur_X = 5;
    Cur_Y = 0;
    LCD_SetCursor(Cur_X, Cur_Y);
  }

  // Relay ON/OFF
  if (KEY_OUT_S) {
    KEY_OUT_S = 0;
    OutState = ON;
    fLCD_updata = 1;
    LCD_DispMode = eTimerCount;
    SET1_TimerState = TIMER1_ON;
    TimeRestart();
    // 時間等於0 一開繼電路
    if (SetTimer1_ON_cnt > 0) {
      RELAY_ON;
    }
    Cur_X = 11;
    Cur_Y = 0;
    LCD_SetCursor(Cur_X, Cur_Y);
  }
}

void TimerCount(void) {
  // SW4短按 Relay OFF 停止計時，回到Normal
  // Relay ON/OFF
  if (KEY_OUT_S) {
    KEY_SELECT_L = 0;
    KEY_SELECT_S =0;
    KEY_UP_S=0;
    KEY_UP_L=0;
    KEY_UP_L_100sm=0;
    KEY_DOWN_S=0;
    KEY_DOWN_L=0;
    KEY_DOWN_L_100ms=0;
    KEY_OUT_S=0;

    OutState = OFF;
    fLCD_updata = 1;
    LCD_DispMode = eNormal;
    RELAY_OFF;
    Cur_X = 11;
    Cur_Y = 1;
    LCD_SetCursor(Cur_X, Cur_Y);
  }
}

void TimeSetting1(void) {
  // 設定第一組時間
  // 1.SW2長按 取消設定，離開
  // 2.SW2短按 確定，設定下一組
  // 3.SW1短按 +1
  // 4.SW1長按 -1(連續)
  // 5.SW3短按 +1
  // 6.SW3長按 -1(連續)

  // 離開
  if (KEY_SELECT_L) {
    KEY_SELECT_L = 0;
    KEY_SELECT_S =0;
    KEY_UP_S=0;
    KEY_UP_L=0;
    KEY_UP_L_100sm=0;
    KEY_DOWN_S=0;
    KEY_DOWN_L=0;
    KEY_DOWN_L_100ms=0;
    KEY_OUT_S=0;
    fLCD_updata = 1;
    short_led_Toggle();
    LCD_DispMode = eNormal;
    Cur_X = 11;
    Cur_Y = 1;
    LCD_SetCursor(Cur_X, Cur_Y);
  }

  // 確定鍵
  if (KEY_SELECT_S) {
    KEY_SELECT_S = 0;
    fLCD_updata = 1;
    short_led_Toggle();
    LCD_DispMode = eTimeSetting2;
    SetTimerN_Value(set_time);
    set_time = 1;
    tempTime_cnt = GetTimerN_Value(set_time);
    EEPROM_WriteWord(EEPROM_TIMER1_ON,SetTimer1_ON_cnt);
    EEPROM_WriteWord(EEPROM_TIMER1_OFF,SetTimer1_OFF_cnt);
    Cur_Y = 1;
    LCD_SetCursor(Cur_X, Cur_Y);
  }

  // 上鍵
  if (KEY_UP_S || KEY_UP_L_100sm) {
    KEY_UP_S = 0;
    KEY_UP_L_100sm = 0;
    fLCD_updata = 1;
    if (tempTime_cnt < MAX_NUM)
      tempTime_cnt++;
    else
      tempTime_cnt = MIN_NUM;
  }

  // 下鍵
  if (KEY_DOWN_S || KEY_DOWN_L_100ms) {
    KEY_DOWN_S = 0;
    KEY_DOWN_L_100ms = 0;
    fLCD_updata = 1;
    if (tempTime_cnt > MIN_NUM)
      tempTime_cnt--;
    else
      tempTime_cnt = MAX_NUM;
  }
}

void TimeSetting2(void) {
  // 設定第一組時間
  // 1.SW2長按 確定
  // 2.SW1短按 +1
  // 3.SW2短按 -1(連續)
  // 2.SW1長按 +1
  // 3.SW2長按 -1(連續)

  // 離開
  if (KEY_SELECT_L) {
    KEY_SELECT_L = 0;
    KEY_SELECT_S =0;
    KEY_UP_S=0;
    KEY_UP_L=0;
    KEY_UP_L_100sm=0;
    KEY_DOWN_S=0;
    KEY_DOWN_L=0;
    KEY_DOWN_L_100ms=0;
    KEY_OUT_S=0;
    fLCD_updata = 1;
    short_led_Toggle();
    LCD_DispMode = eNormal;
    Cur_X = 11;
    Cur_Y = 1;
    LCD_SetCursor(Cur_X, Cur_Y);
  }

  // 確定鍵
  if (KEY_SELECT_S) {
    KEY_SELECT_S = 0;
    fLCD_updata = 1;
    LCD_DispMode = eTimeSetting1;
    SetTimerN_Value(set_time);
    set_time = 0;
    tempTime_cnt = GetTimerN_Value(set_time);
    EEPROM_WriteWord(EEPROM_TIMER1_ON,SetTimer1_ON_cnt);
    EEPROM_WriteWord(EEPROM_TIMER1_OFF,SetTimer1_OFF_cnt);
    Cur_Y = 0;
    LCD_SetCursor(Cur_X, Cur_Y);
  }

  // 上鍵
  if (KEY_UP_S || KEY_UP_L_100sm) {
    KEY_UP_S = 0;
    KEY_UP_L_100sm = 0;
    fLCD_updata = 1;
    if (tempTime_cnt < MAX_NUM)
      tempTime_cnt++;
    else
      tempTime_cnt = MIN_NUM;
  }

  // 下鍵
  if (KEY_DOWN_S || KEY_DOWN_L_100ms) {
    KEY_DOWN_S = 0;
    KEY_DOWN_L_100ms = 0;
    fLCD_updata = 1;
    if (tempTime_cnt > MIN_NUM)
      tempTime_cnt--;
    else
      tempTime_cnt = MAX_NUM;
  }
}

uint16_t GetTimerN_Value(uint8_t x) {
  uint16_t tmpCnt = 0;
  if (x == 0) {
    tmpCnt = SetTimer1_ON_cnt;
  } else if (x == 1) {
    tmpCnt = SetTimer1_OFF_cnt;
  }
  return tmpCnt;
}

void SetTimerN_Value(uint8_t x) {
  if (x == 0) {
    SetTimer1_ON_cnt = tempTime_cnt;
  } else if (x == 1) {
    SetTimer1_OFF_cnt = tempTime_cnt;
  }
}

#define _KEY_H