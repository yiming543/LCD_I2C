#ifndef EEPROM_H
#define EEPROM_H

#include "mcc_generated_files/mcc.h"

//EEPROM位址規劃
#define EEPROM_SET_TIMER1    0
#define EEPROM_SET_TIMER2    8


void POWER_ON_EEPROM_READ(void);

void EEPROM_WriteWord(uint8_t address, uint16_t value);
uint16_t EEPROM_ReadWord(uint8_t address);











#endif  // EEPROM_H
