#include "eeprom.h"
#include "RelayControl.h"

// EEPROM 開機預設值
//0x00-0x01 16bit Count ON
//0x02-0x03 16bit Count OFF

// __EEPROM_DATA(0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0xff, 0xff);
__EEPROM_DATA(0x05, 0x00, 0x03, 0x00, 0x00, 0x00, 0xff, 0xff);
// 0001 ==> 0x0001
__EEPROM_DATA(0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff);

void POWER_ON_EEPROM_READ(void) {
  SetTimer1_ON_cnt = EEPROM_ReadWord(EEPROM_TIMER1_ON);
  SetTimer1_OFF_cnt = EEPROM_ReadWord(EEPROM_TIMER1_OFF);
}

// Usage:
// EEPROM_WriteWord(0, 0x1234);
void EEPROM_WriteWord(uint8_t address, uint16_t value) {
  // Write low byte
  eeprom_write(address, (uint8_t)(value & 0xFF));
  // Write high byte
  eeprom_write(address + 1, (uint8_t)((value >> 8) & 0xFF));
  __delay_ms(5);
}

// Usage example:
// uint16_t value = EEPROM_ReadWord(0);
uint16_t EEPROM_ReadWord(uint8_t address) {
  uint8_t low = eeprom_read(address);      // Read low byte
  uint8_t high = eeprom_read(address + 1); // Read high byte
  return ((uint16_t)high << 8) | low;
  __delay_ms(5);
}