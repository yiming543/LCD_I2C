/*

File:   hd44780_i2c.c

Interface with the HD44780 16x02 LCD display via a i2c backpack which 
requires the display operates in 4-bit mode
 
----- Registers -----

The HD44780U has two 8-bit registers:
    
1. Instruction register (IR)   

The IR stores instruction codes, such as display clear and cursor shift, 
and address information for display data RAM (DDRAM) and character 
generator RAM (CGRAM).

The IR can only be written from the MPU.

2. Data register (DR)

The DR temporarily stores data to be written into DDRAM or CGRAM and 
temporarily stores data to be read from DDRAM or CGRAM. 
Data written into the DR from the MPU is automatically written into
DDRAM or CGRAM by an internal operation. The DR is also used for data 
storage when reading data from DDRAM or CGRAM. 

* When address information is written into the IR, data is read and then 
stored into the DR from DDRAM or CGRAM by an internal operation. 

* Data transfer between the MPU is then completed when the MPU reads the DR. 

* After the read, data in DDRAM or CGRAM at the next address is sent to the 
DR for the next read from the MPU. By the register selector (RS) signal, 
these two registers can be selected (Table 1).

----- Busy Flag (BF) -----

When the busy flag is 1, the HD44780U is in the internal operation mode, 
and the next instruction will not be accepted. 

When RS = 0 and R/W = 1 (Table 1), the busy flag is output to DB7. 

The next instruction must be written after ensuring that the busy flag is 0.

see function for implementation: void lcd_wait() 

----- Address Counter (AC) -----

The address counter (AC) assigns addresses to both DDRAM and CGRAM. 

When an address of an instruction is written into the IR, the address 
information is sent from the IR to the AC. 

Selection of either DDRAM or CGRAM is also determined concurrently by 
the instruction.

After writing into (reading from) DDRAM or CGRAM, the AC is automatically 
incremented by 1 (decremented by 1). 

The AC contents are then output to DB0 to DB6 when RS = 0 and R/W = 1 
(Table 1).

* -- Table 1 Register Selection ------------------------------------ *

    RS | R/W |                          Operation
    --------------------------------------------------------------------- 
    0   0       IR write as an internal operation (display clear, etc.)
    0   1       Read busy flag (DB7) and address counter (DB0 to DB6)
    1   0       DR write as an internal operation (DR to DDRAM or CGRAM)
    1   1       DR read as an internal operation (DDRAM or CGRAM to DR)
    ---------------------------------------------------------------------

* -- 4-bit interfacing to the MPU ------------------------------------ *

    For 4-bit interface data, only four lines (DB4 to DB7) are 
    used for transfer. So bus lines DB0 to DB3 are DISABLED. 

    Data transfer between the HD44780U and the MPU is completed 
    after the 4-bit data has been transferred twice. 

    Order of data transfer: the four high order bits (DB4 to DB7) are
    transferred before the four low order bits (DB0 to DB3).

    The busy flag must be checked (one instruction) after the 4-bit data 
    has been transferred twice. 

    Two more 4-bit operations then transfer the busy flag and address 
    counter data.


* -- Pin Functions ------------------------------------ *

    RS - Selects registers
            0: Instruction register (write)
            1: Data register (write and read)        
    R/W - 0: Write, 1: Read
    E - Starts data read/write

    DB4 to DB7 - data transfer and receive
    DB0 to DB3 - data transfer and receive

    DB3 - backlight
    DB2 - E    
    DB1 - R/W
    DB0 - RS    
    

* -- Instructions ------------------------------------ *

    Ins - RS | R/W | DB7 | DB6 | DB5 | DB4 | DB3 | DB2 | DB1 | DB0

    Clear Display:             00 | 0 0 0 0 | 0 0 0 1 | 

    Return Home:               00 | 0 0 0 0 | 0 0 1 - | 

    Entry Mode Set:            00 | 0 0 0 0 | 0 1 I/D S |

    Display On/Off:            00 | 0 0 0 0 | 1 D C B |
        where D (display), C (cursor), B (blinking)
        
    Cursor/Display Shift:      00 | 0 0 0 1 | S/C R/L - - |    

    Function Set:              00 | 0 0 1 DL | N F - - |
                        
    Read Busy Flag & Address:  01 | BF AC AC AC | AC AC AC AC |
                     

    Increment|Decrement (I/D = 1|0)
    Accompanies Display Shift (S = 1)
    Cursor Move (S/C = 0)
    Shift To Right (R/L = 1)
    Shift To Left (R/L = 0)
    8 bits (DL = 1) - set interface data length DL
    4 bits (DL = 0)
    2 Lines (N = 1)
    1 Line (N = 0)
    5x10 Dots (F = 1)
    5x8 Dots (F = 0)
    Internally Operating (BF = 1)
    Instructions Acceptable (BF = 1)

*/
#include "hd44780_i2c.h"


// 傳送半byte到LCD (高四位), rs=0->命令，rs=1->資料
void PCF8574_LCD_SendNibble(uint8_t nibble, uint8_t rs) {
    uint8_t data = (uint8_t)(nibble << 4) | LCD_BACKLIGHT;
    if (rs) data |= LCD_RS;
    // EN High
    I2C_Write1ByteRegister(PCF8574_ADDR, 0x00, data | LCD_EN);
    __delay_ms(1);
    // EN Low
    I2C_Write1ByteRegister(PCF8574_ADDR, 0x00, data & ~LCD_EN);
}

void PCF8574_LCD_SendByte(uint8_t val, uint8_t rs) {
    PCF8574_LCD_SendNibble(val >> 4, rs);     // High nibble
    PCF8574_LCD_SendNibble(val & 0x0F, rs);   // Low nibble
}

void LCD_Command(uint8_t cmd) {
    PCF8574_LCD_SendByte(cmd, 0);
    __delay_ms(2);
}

void LCD_Data(uint8_t data) {
    PCF8574_LCD_SendByte(data, 1);
    __delay_ms(2);
}

void LCD_Init(void) {
    __delay_ms(50); // LCD啟動等待
    for (uint8_t i = 0; i < 3; i++) {
        PCF8574_LCD_SendNibble(0x03, 0);
        __delay_ms(5);
    }

    PCF8574_LCD_SendNibble(0x02, 0); // 進入4位元模式
    __delay_ms(1);

    //LCD_Command(0x28); // 4-bit, 2 lines, 5x8 dots
    LCD_functionSet();      // 4-bit, 2 lines, 5x8 dots
    LCD_Command(0x0C); // Display ON, Cursor OFF
    LCD_Command(0x06); // Entry mode
    LCD_Command(0x01); // Clear display
    __delay_ms(2);
}

void LCD_SetCursor(uint8_t col, uint8_t row) {
    uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};
    LCD_Command(0x80 | (col + row_offsets[row]));
}

void LCD_Print(const char *str) {
    while(*str) {
        LCD_Data(*str++);
    }
}

// Function set:
// DL = 1; 8-bit interface data
// N = 0; 1-line display
// F = 0; 5 ´ 8 dot character font
void LCD_functionSet(void){
        uint8_t DL=0;//1<<4;        //0:4bit
        uint8_t N=1<<3;             //1:2 line
        uint8_t F=0;//1<<2;         //0:5x8 font

        LCD_Command(FUNCTION_SET|DL|N|F);
        __delay_ms(2);      
}
