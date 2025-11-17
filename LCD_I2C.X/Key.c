#include "Key.h"
#include "TimerEven.h"
#include "mcc_generated_files/pin_manager.h"

// 設定參數：根據需要可以微調
#define KEY_DEBOUNCE_TICK 2   // 單位: 10ms, 20ms
#define KEY_SHORT_TICK    10  // 100ms
#define KEY_LONG_TICK     100 // 1秒

// 按鍵硬體讀取（低電位為按下）
static inline bool key_hw_read(uint8_t idx) {
    switch(idx) {
        case 0: return (Button1_GetValue() == 0); // Button1
        case 1: return (Button2_GetValue() == 0); // Button2
        case 2: return (Button3_GetValue() == 0); // Button3
        case 3: return (Button4_GetValue() == 0); // Button4
        default: return false;
    }
}

KeyInfo_t g_keys[KEY_NUM] = {0};

void Key_Init(void)
{
    for(uint8_t i=0;i<KEY_NUM;i++)
    {
        g_keys[i].state = KEY_IDLE;
        g_keys[i].debounce_cnt = 0;
        g_keys[i].press_cnt = 0;
        g_keys[i].short_press_flag = false;
        g_keys[i].long_press_flag = false;
        g_keys[i].reported = false;
    }
}

// Scan task應於10ms重複呼叫一次
void Key_ScanTask(void)
{
    for(uint8_t i=0;i<KEY_NUM;i++)
    {
        KeyInfo_t* key = &g_keys[i];
        switch(key->state)
        {
            case KEY_IDLE:
                if(key_hw_read(i)) {
                    key->debounce_cnt = 0;
                    key->state = KEY_DEBOUNCE;
                    key->reported = false;
                }
                break;
            case KEY_DEBOUNCE:
                if(key_hw_read(i)) {
                    key->debounce_cnt++;
                    if(key->debounce_cnt > KEY_DEBOUNCE_TICK) {
                        key->state = KEY_PRESS;
                        key->press_cnt = 0;
                    }
                } else {
                    key->state = KEY_IDLE;
                    key->debounce_cnt = 0;
                }
                break;
            case KEY_PRESS:
                if(key_hw_read(i)) {
                    key->press_cnt++;
                    if(key->press_cnt == KEY_LONG_TICK && !key->reported) {
                        key->long_press_flag = true;
                        key->reported = true;
                    }
                    else if(key->press_cnt == KEY_SHORT_TICK && !key->reported) {
                        key->short_press_flag = true;
                        key->reported = true;
                    }
                } else {
                    key->state = KEY_IDLE;
                    key->debounce_cnt = 0;
                    key->press_cnt = 0;
                    key->reported = false;
                }
                break;
        }
    }
}

bool Key_ShortPressed(uint8_t idx)
{
    if(idx < KEY_NUM && g_keys[idx].short_press_flag) {
        g_keys[idx].short_press_flag = false;
        return true;
    }
    return false;
}

bool Key_LongPressed(uint8_t idx)
{
    if(idx < KEY_NUM && g_keys[idx].long_press_flag) {
        g_keys[idx].long_press_flag = false;
        return true;
    }
    return false;
}