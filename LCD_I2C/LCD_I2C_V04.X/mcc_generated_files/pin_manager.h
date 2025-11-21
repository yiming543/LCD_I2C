/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F1936
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set button1 aliases
#define button1_TRIS                 TRISBbits.TRISB0
#define button1_LAT                  LATBbits.LATB0
#define button1_PORT                 PORTBbits.RB0
#define button1_WPU                  WPUBbits.WPUB0
#define button1_ANS                  ANSELBbits.ANSB0
#define button1_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define button1_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define button1_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define button1_GetValue()           PORTBbits.RB0
#define button1_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define button1_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define button1_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define button1_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define button1_SetAnalogMode()      do { ANSELBbits.ANSB0 = 1; } while(0)
#define button1_SetDigitalMode()     do { ANSELBbits.ANSB0 = 0; } while(0)

// get/set button2 aliases
#define button2_TRIS                 TRISBbits.TRISB1
#define button2_LAT                  LATBbits.LATB1
#define button2_PORT                 PORTBbits.RB1
#define button2_WPU                  WPUBbits.WPUB1
#define button2_ANS                  ANSELBbits.ANSB1
#define button2_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define button2_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define button2_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define button2_GetValue()           PORTBbits.RB1
#define button2_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define button2_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define button2_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define button2_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define button2_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define button2_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set button3 aliases
#define button3_TRIS                 TRISBbits.TRISB2
#define button3_LAT                  LATBbits.LATB2
#define button3_PORT                 PORTBbits.RB2
#define button3_WPU                  WPUBbits.WPUB2
#define button3_ANS                  ANSELBbits.ANSB2
#define button3_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define button3_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define button3_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define button3_GetValue()           PORTBbits.RB2
#define button3_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define button3_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define button3_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define button3_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define button3_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define button3_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set button4 aliases
#define button4_TRIS                 TRISBbits.TRISB3
#define button4_LAT                  LATBbits.LATB3
#define button4_PORT                 PORTBbits.RB3
#define button4_WPU                  WPUBbits.WPUB3
#define button4_ANS                  ANSELBbits.ANSB3
#define button4_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define button4_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define button4_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define button4_GetValue()           PORTBbits.RB3
#define button4_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define button4_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define button4_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define button4_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define button4_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define button4_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set short_led aliases
#define short_led_TRIS                 TRISCbits.TRISC0
#define short_led_LAT                  LATCbits.LATC0
#define short_led_PORT                 PORTCbits.RC0
#define short_led_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define short_led_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define short_led_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define short_led_GetValue()           PORTCbits.RC0
#define short_led_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define short_led_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)

// get/set long_led aliases
#define long_led_TRIS                 TRISCbits.TRISC1
#define long_led_LAT                  LATCbits.LATC1
#define long_led_PORT                 PORTCbits.RC1
#define long_led_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define long_led_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define long_led_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define long_led_GetValue()           PORTCbits.RC1
#define long_led_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define long_led_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)

// get/set Relay_en aliases
#define Relay_en_TRIS                 TRISCbits.TRISC2
#define Relay_en_LAT                  LATCbits.LATC2
#define Relay_en_PORT                 PORTCbits.RC2
#define Relay_en_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define Relay_en_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define Relay_en_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define Relay_en_GetValue()           PORTCbits.RC2
#define Relay_en_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define Relay_en_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/