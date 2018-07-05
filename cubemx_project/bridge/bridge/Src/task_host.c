
#include "task_host.h"
#include "task_led.h"
#include "usb_host.h"
#include "usbh_hid_mouse.h"

extern USBH_HandleTypeDef hUsbHostHS;
extern ApplicationTypeDef Appli_state;
uint8_t processHost( struct mouseHID_t * m )
{
	HID_MOUSE_Info_TypeDef * mInfo;
	HID_TypeTypeDef type;
	USBH_Process( &hUsbHostHS );
	if ( Appli_state == APPLICATION_READY )
	{
		type = USBH_HID_GetDeviceType( &hUsbHostHS );
		//if ( type == HID_MOUSE )
		{
			mInfo = USBH_HID_GetMouseInfo( &hUsbHostHS );
		}
	}
	//if ( !mInfo )
	//	return 0;
	//m->x = (*(int8_t *)&(mInfo->x)) + 1;
	//m->y = (*(int8_t *)&(mInfo->y));
	return 1;
}

