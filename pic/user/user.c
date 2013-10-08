/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "system\typedefs.h"
#include "system\usb\usb.h"
#include "io_cfg.h"             // I/O pin mapping
#include "user\user.h"
//#include "user\temperature.h"
#include <spi.h>
/** V A R I A B L E S ********************************************************/
#pragma udata
byte old_sw2,old_sw3;

char input_buffer[64];
char output_buffer[64];
WORD  an1,an2;
rom char welcome[]={"Full-Speed USB - CDC RS-232 Emulation Demo\r\n\r\n"};
rom char ansi_clrscr[]={"\x1b[2J"};         // ANSI Clear Screen Command

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void InitializeUSART(void);
void BlinkUSBStatus(void);
BOOL Switch2IsPressed(void);
//BOOL Switch3IsPressed(void);

void Exercise_Example(void);

void Exercise_01(void);
void Exercise_02(void);
void Exercise_03(void);
void Exercise_04(void);
void Exercise_05(void);
void ResetDAC8522(void);
void LoadDAC8522_A(WORD Val);
/** D E C L A R A T I O N S **************************************************/
#pragma code
void UserInit(void)
{
    InitAllLEDs();
	mInitSwitch2(); 
 // mInitAllSwitches();
    old_sw2 = sw2;
//	mInitDACports();
//	OpenSPI(SPI_FOSC_4, MODE_11, SMPMID);
//	ResetDAC8522();
//	an1._word=1;
//	an2._word=1;
    // old_sw3 = sw3;
    
    //InitTempSensor();

    // InitializeUSART();

}//end UserInit
//================================================================================
void InitializeUSART(void)
{
    TRISCbits.TRISC7=1; // RX
    TRISCbits.TRISC6=0; // TX
    SPBRG = 0x71;
    SPBRGH = 0x02;      // 0x0271 for 48MHz -> 19200 baud
    TXSTA = 0x24;       // TX enable BRGH=1
    RCSTA = 0x90;       // continuous RX
    BAUDCON = 0x08;     // BRG16 = 1
}//end InitializeUSART
//-------------------------------------------------------------------------------
void putsUSART(char *data)
{
  do
  { // Transmit a byte
    while(!TXSTAbits.TRMT);
    TXREG = *data;      // Write the data byte to the USART, 8-bit mode only
  } while(*data++);
}
// *****************************************************************************
void ProcessIO(void)
{//	static byte Am = 0;
	static byte wait=80;
//	static byte K=0;
	byte	Len;
 //  	char input_buffer[65];

//    BlinkUSBStatus();
    // User Application USB tasks
    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)){ return;}//LED_1_On();
    

		
	//  if(wait == 0)wait = 10000U;
//     wait--;
//	if(wait==0)
//	{
/*	 LED_1_Toggle();
	 an1._word =0;	
	 LoadDAC8522_A(an1);
	 an1._word =256;
	 LoadDAC8522_A(an1);
	 an1._word =512;
	 LoadDAC8522_A(an1);
	 an1._word =1023;
	 LoadDAC8522_A(an1);*/

	if(getsUSBUSART(input_buffer, 64))
	{	Len=mCDCGetRxLength();
		if(Len>0)
        { LED_1_Toggle();
		  if(mUSBUSARTIsTxTrfReady())
    	  {    mUSBUSARTTxRam((byte*)input_buffer,Len);
			
		  }
	     if(Switch2IsPressed())  LED_1_Toggle();  
     }

			
/*************
	if(getsUSBUSART(input_buffer, 64))
	{	Len=mCDCGetRxLength();
		input_buffer[Len]=Len;
		if(mUSBUSARTIsTxTrfReady())
    	{
          mUSBUSARTTxRam((byte*)input_buffer,(Len+1));

		}
     }
**************/
   // Exercise_Example();

 /*	if(mUSBUSARTIsTxTrfReady())
    {
        mUSBUSARTTxRam(&Am,1);
		Am++;
	};*/
   }
}//end ProcessIO
//-------------------------------------------------------------------------------
void LoadDAC8522_A(WORD Val)
{	
	Val.HighB._byte &=0x0F;
	DAC_CS=0;
	WriteSPI(Val.HighB._byte);
	WriteSPI(Val.LowB._byte);
	DAC_CS=1;
	DAC_LDA=0;
	DAC_LDA=1;
}
//-------------------------------------------------------------------------------
void ResetDAC8522(void)
{	DAC_CS=1;
	DAC_LDA=1;
	DAC_LDB=1;
	DAC_RS=0;
	DAC_RS=1;
}
//-------------------------------------------------------------------------------

void Exercise_Example(void)
{
    static byte start_up_state = 0;

    if(start_up_state == 0)
    {
        if(Switch2IsPressed())
            start_up_state++;
    }
    else if(start_up_state == 1)
    {
        if(mUSBUSARTIsTxTrfReady())
        {
            putrsUSBUSART(ansi_clrscr);
            start_up_state++;
        }
    }
    else if(start_up_state == 2)
    {
        if(mUSBUSARTIsTxTrfReady())
        {
            putrsUSBUSART("\rMicrochip Technology Inc., 2007\r\n");
            start_up_state++;
        }
    }
    else if(start_up_state == 3)
    {
        if(mUSBUSARTIsTxTrfReady())
        {
            putrsUSBUSART(welcome);
            start_up_state++;
        }
    }

}//end Exercise_Example

//------------------------------------------------------------------------------------
void Exercise_01(void)
{
    /*
     * Write code in this function that sends a literal null-terminated
     * string of text ("Hello World!\r\n") to the PC when switch 2 is
     * pressed.
     *
     * Useful functions:
     *  Switch2IsPressed() returns '1' when switch 2 is pressed.
     *  putrsUSBUSART(...);
     *
     * See examples in Exercise_Example();
     *
     * Remember, you must check if cdc_trf_state is ready for another
     * transfer or not. When it is ready, the value will equal CDC_TX_READY,
     * or use macro: mUSBUSARTIsTxTrfReady()
     */

    /* Insert code here - 3 lines */

    /* End */

}//end Exercise_01
//-------------------------------------------------------------------------------------
rom char ex02_string[]={"Type in a string here.\r\n"};
void Exercise_02(void)
{
    /*
     * Write code in this function that sends a null-terminated string
     * of text stored in program memory pointed to by "ex02_string" to
     * the PC when switch 3 is pressed.
     *
     * ex02_string is declared right above this function.
     *
     * Useful functions:
     *  Switch3IsPressed() returns '1' when switch 3 is pressed.
     *  putrsUSBUSART(...);
     *
     * See examples in Exercise_Example();
     *
     * Remember, you must check if cdc_trf_state is ready for another
     * transfer or not. When it is ready, the value will equal CDC_TX_READY,
     * or use macro: mUSBUSARTIsTxTrfReady()
     */

    /* Insert code here - 3 lines*/

    /* End */

}//end Exercise_02
//------------------------------------------------------------------------------------
void Exercise_03(void)
{
    /*
     * Write code in this function that reads data from USB and
     * toggles LED D4 when the data read equals ASCII character '1' (0x31)
     *
     * Useful functions:
     *  byte getsUSBUSART(char *buffer, byte len)   See cdc.c for details
     *  mLED_4_Toggle();
     *
     * Use input_buffer[] to store data read from USB.
     */

    /* Insert code here - 3 lines */

    /* End */

}//end Exercise_03
//-------------------------------------------------------------------------------------
void Exercise_04(void)
{
    /*
     * Before starting Exercise_04(), comment out the call to Exercise_01()
     * in ProcessIO(); This function will need to check Switch2IsPressed().
     *
     * Write code in this function that sends the following 4 bytes of
     * data: 0x30,0x31,0x32,0x33 when switch 2 is pressed.
     * Note that these data is not null-terminated and is located in
     * the data memory.
     *
     * Useful functions:
     *  Switch2IsPressed() returns '1' when switch 2 is pressed.
     *  mUSBUSARTTxRam(byte *pData, byte len) See cdc.h for details.
     *
     * Use output_buffer[] to store the four bytes data.
     *
     * Remember, you must check if cdc_trf_state is ready for another
     * transfer or not. When it is ready, the value will equal CDC_TX_READY,
     * or use macro: mUSBUSARTIsTxTrfReady()
     */

    /* Insert code here - 7 lines */

    /* End */

}//end Exercise_04
//-----------------------------------------------------------------------------------------
void Exercise_05(void)
{
    /*
     * The PICDEM Full-Speed USB Demo Board is equipped with a
     * temperature sensor. See temperature.c & .h for details.
     *
     * All necessary functions to collect temperature data have
     * been called. This function updates the data a few times
     * every second. The program currently sends out the
     * temperature data to the PC via UART.
     *
     * You can check this by hooking up a serial cable and
     * set your serial port to 19200 baud, 8 bit data, 1 Stop,
     * no parity.
     *
     * The program assumes CPU Frequency = 48 MHz to generate
     * the correct SPBRG value for 19200 baud transmission.
     *
     * Modify the code to send the ASCII string stored in
     * tempString to the PC via USB instead of UART.
     *
     * The temperature data is stored in tempString array in
     * ASCII format and is null-terminated.
     *
     * Useful function:
     *  putsUSBUSART(...);
     *
     *  Note: It is 'puts' and not 'putrs' to be used here.
     *
     * Remember, you must check if cdc_trf_state is ready for another
     * transfer or not. When it is ready, the value will equal CDC_TX_READY,
     * or use macro: mUSBUSARTIsTxTrfReady()
     */

 /*   static word ex05_count;

    if(ex05_count == 0)
    {
        #if defined(PIC18F4550_PICDEM_FS_USB)
        AcquireTemperature();               // Read temperature from sensor
        #endif
        UpdateCelsiusASCII();               // Convert to ASCII, stored in
                                            // "tempString", See temperature.c

        // Modify the code below - 3 lines 

            putsUSART(tempString);
            ex05_count = 10000;

        
    }
    else
        ex05_count--;
	*/
}//end Exercise_05
//=============================================================================
/******************************************************************************
 * Function:        void BlinkUSBStatus(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        BlinkUSBStatus turns on and off LEDs corresponding to
 *                  the USB device state.
 *
 * Note:            mLED macros can be found in io_cfg.h
 *                  usb_device_state is declared in usbmmap.c and is modified
 *                  in usbdrv.c, usbctrltrf.c, and usb9.c
 *****************************************************************************/
void BlinkUSBStatus(void)
{
    static word led_count=0;

    if(led_count == 0)led_count = 10000U;
    led_count--;

    #define LED_Both_Off()         {LED_1_Off();LED_2_Off();}
    #define LED_Both_On()          {LED_1_On();LED_2_On();}
    #define LED_Only_1_On()        {LED_1_On();LED_2_Off();}
    #define LED_Only_2_On()        {LED_1_Off();LED_2_On();}

    if(UCONbits.SUSPND == 1)
    {
        if(led_count==0)
        {
            LED_1_Toggle();
            LED_2 = LED_1;        // Both blink at the same time
        }//end if
    }
    else
    {
        if(usb_device_state == DETACHED_STATE)
        {
            LED_Both_Off();
        }
        else if(usb_device_state == ATTACHED_STATE)
        {
            LED_Both_On();
        }
        else if(usb_device_state == POWERED_STATE)
        {
            LED_Only_1_On();
        }
        else if(usb_device_state == DEFAULT_STATE)
        {
            LED_Only_2_On();
        }
        else if(usb_device_state == ADDRESS_STATE)
        {
            if(led_count == 0)
            {
                LED_1_Toggle();
                LED_2_Off();
            }//end if
        }
        else if(usb_device_state == CONFIGURED_STATE)
        {
            if(led_count==0)
            {
                LED_1_Toggle();
                LED_2 = !LED_1;       // Alternate blink
            }//end if
        }//end if(...)
    }//end if(UCONbits.SUSPND...)

}//end BlinkUSBStatus
//==========================================================================
BOOL Switch2IsPressed(void)
{
    if(sw2 != old_sw2)
    {
        old_sw2 = sw2;                  // Save new value
        if(sw2 == 0)                    // If pressed
            return TRUE;                // Was pressed
    }//end if
    return FALSE;                       // Was not pressed
}//end Switch2IsPressed
//==========================================================================
/*BOOL Switch3IsPressed(void)
{
    if(sw3 != old_sw3)
    {
        old_sw3 = sw3;                  // Save new value
        if(sw3 == 0)                    // If pressed
            return TRUE;                // Was pressed
    }//end if
    return FALSE;                       // Was not pressed
}//end Switch3IsPressed
*/
/** EOF user.c ***************************************************************/
