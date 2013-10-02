#ifndef USBCFG_H
#define USBCFG_H

/** D E F I N I T I O N S *******************************************/
#define MAX_NUM_INT             1   // For tracking Alternate Setting
#define EP0_BUFF_SIZE           8   // Valid Options: 8, 16, 32, or 64 bytes.
									// There is very little advantage in using 
									// more than 8 bytes on EP0 IN/OUT, so 8 is the
									// recommended value.

/* Parameter definitions are defined in usbdrv.h */
#define MODE_PP                 _PPBM0
#define UCFG_VAL                _PUEN|_TRINT|_FS|MODE_PP


/* Uncomment only the hardware platform that you are using*/
//#define PIC18F4550_PICDEM_FS_USB
//#define PIC18F87J50_FS_USB_PIM
//#define YOUR_BOARD	


//#if defined(PIC18F4550_PICDEM_FS_USB)
//	#define USE_SELF_POWER_SENSE_IO		
//    #define USE_USB_BUS_SENSE_IO

//#elif defined(PIC18F87J50_FS_USB_PIM)
    //#define USE_USB_BUS_SENSE_IO		//JP1 must be in R-U position to use this feature on this board		

/*If using the YOUR_BOARD selection, uncomment below section as appropriate for your hardware*/
//#elif defined(YOUR_BOARD)
	//#define USE_SELF_POWER_SENSE_IO	//See main.c and MCHPFSUSB Firmware User's Guide
   	//#define USE_USB_BUS_SENSE_IO		//(DS51679) for more details about these features.


//#else
//    #error Not a supported board (yet), See __FILE__, line __LINE__, or double click on this text.
//See above commented section.  You need to select the features your hardware will be using.
//#endif

/** D E V I C E  C L A S S  U S A G E *******************************/
#define USB_USE_CDC

/*
 * MUID = Microchip USB Class ID
 * Used to identify which of the USB classes owns the current
 * session of control transfer over EP0
 */
#define MUID_NULL               0
#define MUID_USB9               1
#define MUID_HID                2
#define MUID_CDC                3
#define MUID_MSD                4

/** E N D P O I N T S  A L L O C A T I O N **************************/
/*
 * See usbmmap.c for an explanation of how the endpoint allocation works
 */

/* CDC */
#define CDC_COMM_INTF_ID        0x00
#define CDC_COMM_UEP            UEP2
#define CDC_INT_BD_IN           ep2Bi
#define CDC_INT_EP_SIZE         8

#define CDC_DATA_INTF_ID        0x01
#define CDC_DATA_UEP            UEP3
#define CDC_BULK_BD_OUT         ep3Bo
#define CDC_BULK_OUT_EP_SIZE    64
#define CDC_BULK_BD_IN          ep3Bi
#define CDC_BULK_IN_EP_SIZE     64

#define MAX_EP_NUMBER           3           // UEP3

#endif //USBCFG_H
