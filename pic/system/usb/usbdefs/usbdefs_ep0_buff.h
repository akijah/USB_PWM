#ifndef USBDEFS_EP0_BUFF_H
#define USBDEFS_EP0_BUFF_H

/** I N C L U D E S **********************************************************/
#include "system\typedefs.h"
#include "autofiles\usbcfg.h"       // usbcfg.h contains required definitions

/******************************************************************************
 * CTRL_TRF_SETUP:
 *
 * Every setup packet has 8 bytes.
 * However, the buffer size has to equal the EP0_BUFF_SIZE value specified
 * in autofiles\usbcfg.h
 * The value of EP0_BUFF_SIZE can be 8, 16, 32, or 64.
 *
 * First 8 bytes are defined to be directly addressable to improve speed
 * and reduce code size.
 * Bytes beyond the 8th byte have to be accessed using indirect addressing.
 *****************************************************************************/
typedef union _CTRL_TRF_SETUP
{
    /** Array for indirect addressing ****************************************/
    struct
    {
        byte _byte[EP0_BUFF_SIZE];
    };
    
    /** Standard Device Requests *********************************************/
    struct
    {
        byte bmRequestType;
        byte bRequest;    
        word wValue;
        word wIndex;
        word wLength;
    };
    struct
    {
        unsigned :8;
        unsigned :8;
        WORD W_Value;
        WORD W_Index;
        WORD W_Length;
    };
    struct
    {
        unsigned Recipient:5;           //Device,Interface,Endpoint,Other
        unsigned RequestType:2;         //Standard,Class,Vendor,Reserved
        unsigned DataDir:1;             //Host-to-device,Device-to-host
        unsigned :8;
        byte bFeature;                  //DEVICE_REMOTE_WAKEUP,ENDPOINT_HALT
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
    };
    struct
    {
        unsigned :8;
        unsigned :8;
        byte bDscIndex;                 //For Configuration and String DSC Only
        byte bDscType;                  //Device,Configuration,String
        word wLangID;                   //Language ID
        unsigned :8;
        unsigned :8;
    };
    struct
    {
        unsigned :8;
        unsigned :8;
        BYTE bDevADR;                   //Device Address 0-127
        byte bDevADRH;                  //Must equal zero
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
    };
    struct
    {
        unsigned :8;
        unsigned :8;
        byte bCfgValue;                 //Configuration Value 0-255
        byte bCfgRSD;                   //Must equal zero (Reserved)
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
    };
    struct
    {
        unsigned :8;
        unsigned :8;
        byte bAltID;                    //Alternate Setting Value 0-255
        byte bAltID_H;                  //Must equal zero
        byte bIntfID;                   //Interface Number Value 0-255
        byte bIntfID_H;                 //Must equal zero
        unsigned :8;
        unsigned :8;
    };
    struct
    {
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
        byte bEPID;                     //Endpoint ID (Number & Direction)
        byte bEPID_H;                   //Must equal zero
        unsigned :8;
        unsigned :8;
    };
    struct
    {
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned EPNum:4;               //Endpoint Number 0-15
        unsigned :3;
        unsigned EPDir:1;               //Endpoint Direction: 0-OUT, 1-IN
        unsigned :8;
        unsigned :8;
        unsigned :8;
    };
    /** End: Standard Device Requests ****************************************/
    
} CTRL_TRF_SETUP;

/******************************************************************************
 * CTRL_TRF_DATA:
 *
 * Buffer size has to equal the EP0_BUFF_SIZE value specified
 * in autofiles\usbcfg.h
 * The value of EP0_BUFF_SIZE can be 8, 16, 32, or 64.
 *
 * First 8 bytes are defined to be directly addressable to improve speed
 * and reduce code size.
 * Bytes beyond the 8th byte have to be accessed using indirect addressing.
 *****************************************************************************/
typedef union _CTRL_TRF_DATA
{
    /** Array for indirect addressing ****************************************/
    struct
    {
        byte _byte[EP0_BUFF_SIZE];
    };
    
    /** First 8-byte direct addressing ***************************************/
    struct
    {
        byte _byte0;
        byte _byte1;
        byte _byte2;
        byte _byte3;
        byte _byte4;
        byte _byte5;
        byte _byte6;
        byte _byte7;
    };
    struct
    {
        word _word0;
        word _word1;
        word _word2;
        word _word3;
    };

} CTRL_TRF_DATA;

#endif //USBDEFS_EP0_BUFF_H
