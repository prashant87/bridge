
#include "task_host.h"
#include "task_led.h"
#include "usbh_hid_mouse.h"

extern USBH_HandleTypeDef hUsbHostHS;
uint8_t processHost( struct mouseHID_t * m )
{
	HID_MOUSE_Info_TypeDef * mInfo;
	USBH_Process( &hUsbHostHS );
	mInfo = USBH_HID_GetMouseInfo( &hUsbHostHS );
	//if ( !mInfo )
	//	return 0;
	//m->x = (*(int8_t *)&(mInfo->x)) + 1;
	//m->y = (*(int8_t *)&(mInfo->y));
	return 1;
}

