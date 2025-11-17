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

// get/set Button4 aliases
#define Button4_TRIS                 TRISBbits.TRISB2
#define Button4_LAT                  LATBbits.LATB2
#define Button4_PORT                 PORTBbits.RB2
#define Button4_WPU                  WPUBbits.WPUB2
#define Button4_ANS                  ANSELBbits.ANSB2
#define Button4_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define Button4_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define Button4_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define Button4_GetValue()           PORTBbits.RB2
#define Button4_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define Button4_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define Button4_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define Button4_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define Button4_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define Button4_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set Button3 aliases
#define Button3_TRIS                 TRISBbits.TRISB3
#define Button3_LAT                  LATBbits.LATB3
#define Button3_PORT                 PORTBbits.RB3
#define Button3_WPU                  WPUBbits.WPUB3
#define Button3_ANS                  ANSELBbits.ANSB3
#define Button3_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define Button3_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define Button3_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define Button3_GetValue()           PORTBbits.RB3
#define Button3_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define Button3_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define Button3_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define Button3_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define Button3_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define Button3_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set Button2 aliases
#define Button2_TRIS                 TRISBbits.TRISB4
#define Button2_LAT                  LATBbits.LATB4
#define Button2_PORT                 PORTBbits.RB4
#define Button2_WPU                  WPUBbits.WPUB4
#define Button2_ANS                  ANSELBbits.ANSB4
#define Button2_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define Button2_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define Button2_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define Button2_GetValue()           PORTBbits.RB4
#define Button2_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define Button2_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define Button2_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define Button2_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define Button2_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define Button2_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set Button1 aliases
#define Button1_TRIS                 TRISBbits.TRISB5
#define Button1_LAT                  LATBbits.LATB5
#define Button1_PORT                 PORTBbits.RB5
#define Button1_WPU                  WPUBbits.WPUB5
#define Button1_ANS                  ANSELBbits.ANSB5
#define Button1_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define Button1_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define Button1_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define Button1_GetValue()           PORTBbits.RB5
#define Button1_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define Button1_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define Button1_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define Button1_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define Button1_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define Button1_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

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