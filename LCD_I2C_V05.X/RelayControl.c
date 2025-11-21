#include "RelayControl.h"
#include "Key.h"
#include "TimerEven.h"
#include "hd44780_i2c.h"
#include <string.h>

// mode 1:1S
uint8_t TimeMode;
uint8_t AdjustMode;
uint8_t Cursor_pos = 0;

char buf[17] = {0};
// uint8_t Digital[4]={0};
uint16_t SetTimer1_cnt = 1;
uint8_t SetTimer1_digi[4] = {0};

uint16_t SetTimer2_cnt = 1;
uint8_t SetTimer2_digi[4] = {0};

bool OutState = OFF;
char RelayState_buf[3] = {0};

bool TimerState = OFF;

uint8_t LCD_DispMode = 0;
bool fLCD_updata = 0;

void RelayControl_Init(void) {
  // 開機預設模式為1秒
  RELAY_OFF;
  TimerState = OFF;
  strncpy(RelayState_buf, "OFF", sizeof(RelayState_buf));
  // TimeMode = e1_000S;
  // TimeMode = e0_100S;
  TimeMode = e0_010S;
  LCD_DispMode = eNormal;
  AdjustMode = eADJ_T1_DIG1;
  fLCD_updata=1;
}

void TimeModeSelect(void) {
  switch (TimeMode) {
  case e1_000S:
    T1_1000ms_cnt = 0;
    x100T_cnt = 0;
    fT1_1second = 0;
    break;
  case e0_100S:
    T1_100ms_cnt = 0;
    x10T_cnt = 0;
    fT1_100ms = 0;
    break;
  case e0_010S:
    x1T_cnt = 0;
    fT1_10ms = 0;
    break;
  // case e0_001S:
  //   SetTimer1_cnt = 1000;
  //   SetTimer2_cnt = 1;
  //   break;
  default:
    T1_1000ms_cnt = 0;
    x100T_cnt = 0;
    fT1_1second = 0;
    T1_100ms_cnt = 0;
    x10T_cnt = 0;
    fT1_100ms = 0;
    x1T_cnt = 0;
    fT1_10ms = 0;
    break;
  }
  xComm_cnt = 0;
  fT1_TimerUp = 0;
}

// void Number2Digital(uint16_t Num, uint8_t *digital1, uint8_t *digital2,
// uint8_t *digital3, uint8_t *digital4) {
void Number2Digital(uint16_t Num, uint8_t *digiNum) {
  uint16_t temp = 0;
  temp = Num / 1000;
  digiNum[0] = (uint8_t)temp;
  Num = Num - (temp * 1000); // new Num

  temp = Num / 100;
  digiNum[1] = (uint8_t)temp;

  Num = Num - (temp * 100); // new Num

  temp = Num / 10;
  digiNum[2] = (uint8_t)temp;

  digiNum[3] = (uint8_t)(Num % 10);
}

void Digital2Number(uint16_t *Num, uint8_t *digital) {
  uint16_t temp1 = (uint16_t)digital[0];
  uint16_t temp2 = (uint16_t)digital[1];
  uint16_t temp3 = (uint16_t)digital[2];
  uint16_t temp4 = (uint16_t)digital[3];

  *Num = temp1 * 1000 + temp2 * 100 + temp3 * 10 + temp4;
}

void DispNormal(uint8_t mode, uint8_t n, uint16_t Num, char *buf) {
  // uint8_t digi1, digi2, digi3, digi4;
  uint8_t digital[4] = {0};
  char temp_str[3] = {0};

  // Number2Digital(Num, &digi1, &digi2, &digi3, &digi4);
  Number2Digital(Num, digital);

  // 第1行顯示OUT ON/OFF，第2行空白
  if (n == _T1_) {
    strncpy(temp_str, RelayState_buf, sizeof(RelayState_buf));
  } else {
    strncpy(temp_str, "   ", sizeof(RelayState_buf));
  }

  switch (mode) {
  case e1_000S:
    // 0001.~9999.S
    sprintf(buf, "T%d:%d%d%d%d. S   %s", n, digital[0], digital[1], digital[2],
            digital[3], temp_str);
    break;
  case e0_100S:
    // 000.1~999.9S
    sprintf(buf, "T%d:%d%d%d.%d S   %s", n, digital[0], digital[1], digital[2],
            digital[3], temp_str);
    break;
  case e0_010S:
    // 00.01~99.99S
    sprintf(buf, "T%d:%d%d.%d%d S   %s", n, digital[0], digital[1], digital[2],
            digital[3], temp_str);
    break;
  default:
    break;
  }
}

void DispFunctionSet(uint8_t mode, uint8_t n, uint16_t Num, char *buf) {

  switch (mode) {
  case e1_000S:
    // 0001.~9999.S
    sprintf(buf, "Unit:1.00 S");
    break;
  case e0_100S:
    // 000.1~999.9S
    sprintf(buf, "Unit:0.10 S");
    break;
  case e0_010S:
    // 00.01~99.99S
    sprintf(buf, "Unit:0.01 S");
    break;
  default:
    break;
  }
}

void DispTimeAdjustment(uint8_t mode, uint8_t n, uint16_t Num, char *buf) {
  // uint8_t digi1, digi2, digi3, digi4;
  uint8_t digital[4] = {0};
  char temp_str[3] = {0};

  // 第1行顯示OUT ON/OFF，第2行空白
  if (n == _T1_) {
    // strncpy(temp_str, RelayState_buf, sizeof(RelayState_buf));
    strncpy(temp_str, "   ", sizeof(RelayState_buf));
    digital[0] = SetTimer1_digi[0];
    digital[1] = SetTimer1_digi[1];
    digital[2] = SetTimer1_digi[2];
    digital[3] = SetTimer1_digi[3];
  } else {
    strncpy(temp_str, "   ", sizeof(RelayState_buf));
    digital[0] = SetTimer2_digi[0];
    digital[1] = SetTimer2_digi[1];
    digital[2] = SetTimer2_digi[2];
    digital[3] = SetTimer2_digi[3];
  }

  // sprintf(buf, "T%d:%d%d%d%d.S    %s", n, digital[0], digital[1], digital[2],
  //         digital[3], temp_str);

  switch (mode) {
  case e1_000S:
    // 0001.~9999.S
    sprintf(buf, "T%d:%d%d%d%d. S   %s", n, digital[0], digital[1], digital[2],
            digital[3], temp_str);
    break;
  case e0_100S:
    // 000.1~999.9S
    sprintf(buf, "T%d:%d%d%d.%d S   %s", n, digital[0], digital[1], digital[2],
            digital[3], temp_str);
    break;
  case e0_010S:
    // 00.01~99.99S
    sprintf(buf, "T%d:%d%d.%d%d S   %s", n, digital[0], digital[1], digital[2],
            digital[3], temp_str);
    break;
  default:
    break;
  }
}

void KeepTimerCounter(void) {
  if (OutState == OFF) {
    // Relay off
    RELAY_OFF;
  } else {
    // 計時中
    if (fT1_TimerUp) {
      fT1_TimerUp = 0;
      if (TimerState == TIMER1) {
        if (xComm_cnt >= SetTimer1_cnt) {
          x1T_cnt = 0;
          x10T_cnt = 0;
          x100T_cnt = 0;
          RELAY_OFF;
          // short_led_Toggle();
          TimerState = TIMER2;
        }
      } else { // TIMER2
        if (xComm_cnt >= SetTimer2_cnt) {
          x1T_cnt = 0;
          x10T_cnt = 0;
          x100T_cnt = 0;
          RELAY_ON;
          // short_led_Toggle();
          TimerState = TIMER1;
        }
      }
    }
  }
}

void Normal(void) {
  // FunctionSet
  if (KEY_SELECT_L) {
    KEY_SELECT_L = 0;
    fLCD_updata=1;
    LCD_DispMode = eFunctionSet;
    OutState = OFF;
    strncpy(RelayState_buf, "OFF", sizeof(RelayState_buf));
    RELAY_OFF;
    short_led_Toggle();
  }

  // Relay ON/OFF
  if (KEY_OUT_S) {
    KEY_OUT_S = 0;
    OutState = !OutState;
    fLCD_updata=1;
    if (OutState) {
      TimeModeSelect();
      strncpy(RelayState_buf, " ON", sizeof(RelayState_buf));
      RELAY_ON;
    } else {
      RELAY_OFF;
      strncpy(RelayState_buf, "OFF", sizeof(RelayState_buf));
    }
  }
}

void FunctionSet(void) {
  // start there
  if (KEY_UP_S) {
    KEY_UP_S = 0;
    fLCD_updata=1;
    TimeMode++;
    if (TimeMode > e0_010S)
      TimeMode = e1_000S;
    short_led_Toggle();
  }

  if (KEY_SELECT_L) {
    KEY_SELECT_L = 0;
    fLCD_updata=1;
    LCD_DispMode = eTimeAdjustment;
    AdjustMode = eADJ_T1_DIG1;
    Number2Digital(SetTimer1_cnt, SetTimer1_digi);
    Number2Digital(SetTimer1_cnt, SetTimer2_digi);
    short_led_Toggle();
  }

  if (KEY_DOWN_S) {
    KEY_DOWN_S = 0;
    fLCD_updata=1;
    TimeMode--;
    if (TimeMode < e1_000S)
      TimeMode = e0_010S;
    short_led_Toggle();
  }
}

void TimeAdjustment(void) {
  uint8_t *DigPtr = SetTimer1_digi;

  switch (AdjustMode) {
  case eADJ_T1_DIG1:
    DigPtr = &SetTimer1_digi[0];
    Cursor_pos = 3;
    break;
  case eADJ_T1_DIG2:
    DigPtr = &SetTimer1_digi[1];
    Cursor_pos = 4;
    break;
  case eADJ_T1_DIG3:
    DigPtr = &SetTimer1_digi[2];
    if (TimeMode == e1_000S) {
      Cursor_pos = 5;
    } else if (TimeMode == e0_100S) {
      Cursor_pos = 5;
    } else if (TimeMode == e0_010S) {
      Cursor_pos = 5 + 1;
    }
    break;
  case eADJ_T1_DIG4:
    DigPtr = &SetTimer1_digi[3];
    if (TimeMode == e1_000S) {
      Cursor_pos = 6;
    } else if (TimeMode == e0_100S) {
      Cursor_pos = 6 + 1;
    } else if (TimeMode == e0_010S) {
      Cursor_pos = 6 + 1;
    }
    break;
  case eADJ_T2_DIG1:
    DigPtr = &SetTimer2_digi[0];
    Cursor_pos = 0x43;
    break;
  case eADJ_T2_DIG2:
    DigPtr = &SetTimer2_digi[1];
    Cursor_pos = 0x44;
    break;
  case eADJ_T2_DIG3:
    DigPtr = &SetTimer2_digi[2];
    if (TimeMode == e1_000S) {
      Cursor_pos = 0x45;
    } else if (TimeMode == e0_100S) {
      Cursor_pos = 0x45;
    } else if (TimeMode == e0_010S) {
      Cursor_pos = 0x45 + 1;
    }
    break;
  case eADJ_T2_DIG4:
    DigPtr = &SetTimer2_digi[3];
    if (TimeMode == e1_000S) {
      Cursor_pos = 0x46;
    } else if (TimeMode == e0_100S) {
      Cursor_pos = 0x46 + 1;
    } else if (TimeMode == e0_010S) {
      Cursor_pos = 0x46 + 1;
    }
    break;

  default:
    break;
  }

  if (KEY_UP_S) {
    KEY_UP_S = 0;
    fLCD_updata=1;
    (*DigPtr)++;
    if (TimeMode > MAX_NUM)
      *DigPtr = 0;
    short_led_Toggle();
  }

  if (KEY_SELECT_S) {
    KEY_SELECT_S = 0;
    fLCD_updata=1;
    AdjustMode++;
    if (AdjustMode > eADJ_T2_DIG4)
      AdjustMode = eADJ_T1_DIG1;
    short_led_Toggle();
  }

  if (KEY_DOWN_S) {
    KEY_DOWN_S = 0;
    fLCD_updata=1;
    if (TimeMode == MIN_NUM)
      *DigPtr = 9;
    else
      (*DigPtr)--;

    short_led_Toggle();
  }

  if (KEY_SELECT_L) {
    KEY_SELECT_L = 0;
    fLCD_updata=1;
    short_led_Toggle();
    LCD_DispMode = eNormal;
    Digital2Number(&SetTimer1_cnt, SetTimer1_digi);
    Digital2Number(&SetTimer2_cnt, SetTimer2_digi);
  }
}

#define _KEY_H