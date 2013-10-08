#ifndef IO_CFG_H
#define IO_CFG_H

/** I N C L U D E S *************************************************/
#include "autofiles\usbcfg.h"

/** T R I S *********************************************************/
#define INPUT_PIN           1
#define OUTPUT_PIN          0


//#if defined(PIC18F4550_PICDEM_FS_USB)
/** U S B ***********************************************************/
//#define tris_usb_bus_sense  TRISAbits.TRISA1    // Input

//#if defined(USE_USB_BUS_SENSE_IO)
//#define usb_bus_sense       PORTAbits.RA1
//#else
#define usb_bus_sense       1
//#endif

//#define tris_self_power     TRISAbits.TRISA2    // Input

//#if defined(USE_SELF_POWER_SENSE_IO)
//#define self_power          PORTAbits.RA2
//#else
#define self_power          1					// Used by USBStdGetStatusHandler() in usb9.c
//#endif										

// External Transceiver Interface
//#define tris_usb_vpo        TRISBbits.TRISB3    // Output
//#define tris_usb_vmo        TRISBbits.TRISB2    // Output
//#define tris_usb_rcv        TRISAbits.TRISA4    // Input
//#define tris_usb_vp         TRISCbits.TRISC5    // Input
//#define tris_usb_vm         TRISCbits.TRISC4    // Input
//#define tris_usb_oe         TRISCbits.TRISC1    // Output

//#define tris_usb_suspnd     TRISAbits.TRISA3    // Output

/** L E D ***********************************************************/
/*#define mInitAllLEDs()      LATD &= 0xF0; TRISD &= 0xF0;

#define mLED_1              LATDbits.LATD0
#define mLED_2              LATDbits.LATD1
#define mLED_3              LATDbits.LATD2
#define mLED_4              LATDbits.LATD3

#define mLED_1_On()         mLED_1 = 1;
#define mLED_2_On()         mLED_2 = 1;
#define mLED_3_On()         mLED_3 = 1;
#define mLED_4_On()         mLED_4 = 1;

#define mLED_1_Off()        mLED_1 = 0;
#define mLED_2_Off()        mLED_2 = 0;
#define mLED_3_Off()        mLED_3 = 0;
#define mLED_4_Off()        mLED_4 = 0;

#define mLED_1_Toggle()     mLED_1 = !mLED_1;
#define mLED_2_Toggle()     mLED_2 = !mLED_2;
#define mLED_3_Toggle()     mLED_3 = !mLED_3;
#define mLED_4_Toggle()     mLED_4 = !mLED_4;
*/

//#define InitAllLEDs()     LATB &= 0xE7; TRISB &= 0xE7;
//#define LED_1              LATBbits.LATB4
//#define LED_2              LATBbits.LATB3
#define InitAllLEDs()     LATC &= 0xF9; TRISC &= 0xF9;
#define LED_1              LATCbits.LATC1
#define LED_2              LATCbits.LATC2

#define LED_1_On()         LED_1 = 1;
#define LED_1_Off()        LED_1 = 0;
#define LED_1_Toggle()     LED_1 = !LED_1;
#define LED_2_On()         LED_2 = 1;
#define LED_2_Off()        LED_2 = 0;
#define LED_2_Toggle()     LED_2 = !LED_2;

/** S W I T C H *****************************************************/
//#define mInitAllSwitches()  TRISBbits.TRISB4=1;TRISBbits.TRISB5=1;
//#define mInitSwitch2()      TRISBbits.TRISB4=1;
//#define mInitSwitch3()      TRISBbits.TRISB5=1;
//#define sw2                 PORTBbits.RB4
//#define sw3                 PORTBbits.RB5

//#define mInitAllSwitches()  TRISBbits.TRISB2=1;
#define mInitSwitch2()      TRISBbits.TRISB2=1;
//#define mInitSwitch3()      TRISBbits.TRISB5=1;
#define sw2                 PORTBbits.RB2
//#define sw3                 PORTBbits.RB5
//** PWM----------------------------------------------------------------
//CCP1=RC2(pin13) CCP2=RC1(pin12) Led or RB3 (pin24)
#define mInitPWM()          TRISCbits.TRISC2=0;TRISBbits.TRISB3=0;
#define PWM_1              LATCbits.LATC2
#define PWM_2              LATBbits.LATB3

#define PWM_1_On()         PWM_1 = 1;
#define PWM_1_Off()        PWM_1 = 0;
#define PWM_1_Toggle()     PWM_1 = !PWM_1;
#define PWM_2_On()         PWM_2 = 1;
#define PWM_2_Off()        PWM_2 = 0;
#define PWM_2_Toggle()     PWM_2 = !PWM_2;

/** P O T ***********************************************************/
#define mInitPOT()          TRISAbits.TRISA0=1;ADCON0=0x01;ADCON2=0x3C;

/** DAC8522 **********************************************************/
#define mInitDACports()          TRISC&=0x78; LATC|=0x87; TRISB &=0xF9; LATB|=0x06;
#define DAC_CS             LATBbits.LATB2
#define DAC_RS             LATCbits.LATC2
#define DAC_LDA            LATCbits.LATC1
#define DAC_LDB            LATCbits.LATC0

/** S P I : Chip Select Lines ***************************************/
//CKP=1 CKE=0 SMP=0 Fosc/4=12mbps
#define mInitSPI()          SSPSTAT=0x00; SSPCON1=0x30;ADCON2=0x3C;
//#define tris_cs_temp_sensor TRISBbits.TRISB2    // Output
//#define cs_temp_sensor      LATBbits.LATB2

//#define tris_cs_sdmmc       TRISBbits.TRISB3    // Output
//#define cs_sdmmc            LATBbits.LATB3

/** S D M M C *******************************************************/
//#define TRIS_CARD_DETECT    TRISBbits.TRISB4    // Input
//#define CARD_DETECT         PORTBbits.RB4

//#define TRIS_WRITE_DETECT   TRISAbits.TRISA4    // Input
//#define WRITE_DETECT        PORTAbits.RA4

/********************************************************************/

