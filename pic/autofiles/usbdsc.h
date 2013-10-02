/*********************************************************************
 * Descriptor specific type definitions are defined in:
 * system\usb\usbdefs\usbdefs_std_dsc.h
 ********************************************************************/

#ifndef USBDSC_H
#define USBDSC_H

/** I N C L U D E S *************************************************/
#include "system\typedefs.h"
#include "autofiles\usbcfg.h"

#if defined(USB_USE_CDC)
#include "system\usb\class\cdc\cdc.h"
#endif

#include "system\usb\usb.h"

/** D E F I N I T I O N S *******************************************/

#define CFG01 rom struct                            \
{   USB_CFG_DSC             cd01;                   \
    USB_INTF_DSC            i01a00;                 \
    USB_CDC_HEADER_FN_DSC   cdc_header_fn_i01a00;   \
    USB_CDC_ACM_FN_DSC      cdc_acm_fn_i01a00;      \
    USB_CDC_UNION_FN_DSC    cdc_union_fn_i01a00;    \
    USB_CDC_CALL_MGT_FN_DSC cdc_call_mgt_fn_i01a00; \
    USB_EP_DSC              ep02i_i01a00;           \
    USB_INTF_DSC            i02a00;                 \
    USB_EP_DSC              ep03o_i02a00;           \
    USB_EP_DSC              ep03i_i02a00;           \
} cfg01

/** E X T E R N S ***************************************************/
extern rom USB_DEV_DSC device_dsc;
extern CFG01;
extern rom const unsigned char *rom USB_CD_Ptr[];
extern rom const unsigned char *rom USB_SD_Ptr[];

extern rom pFunc ClassReqHandler[1];

#endif //USBDSC_H
