
#ifndef HD44780_I2C_H
#define HD44780_I2C_H

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c_master_example.h"

#define CLEAR_DISPLAY 0x01
#define RETURN_HOME 0x02
#define FUNCTION_SET 0x20
#define DISP_ON_CUR_OFF 0x0C
#define DISP_ON_CUR_ON 0x0E
#define DISP_ON_CUR_ON_BLOCK 0x0F
// PCF8574定義
#define PCF8574_ADDR 0x27  // 根據模組調整

// LCD透過PCF8574的位元對應
#define LCD_RS 0x01
#define LCD_EN 0x04
#define LCD_BACKLIGHT 0x08

#define LCD_CMD 0
#define LCD_DATA 1

// void PCF8574_LCD_SendNibble(uint8_t nibble, uint8_t rs);
// void PCF8574_LCD_SendByte(uint8_t val, uint8_t rs);
// void LCD_Command(uint8_t cmd);
// void LCD_Data(uint8_t data);
void LCD_Init(void);
void LCD_SetCursor(uint8_t col, uint8_t row);
void LCD_Print(const char *str);
void LCD_Command(uint8_t cmd);
// void LCD_functionSet(void);

#endif /* HD44780_I2C_H */