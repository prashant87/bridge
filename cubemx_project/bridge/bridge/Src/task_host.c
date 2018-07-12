
#include "task_host.h"
#include "task_led.h"
#include "usb_host.h"
#include "usbh_hid_mouse.h"

static USBH_HandleTypeDef hUsbHostHS;
static ApplicationTypeDef Appli_state = APPLICATION_IDLE;
static void myUserProcess(USBH_HandleTypeDef *phost, uint8_t id);

void taskHostInit( void )
{
	  USBH_Init(&hUsbHostHS, myUserProcess, HOST_HS);
	  USBH_RegisterClass(&hUsbHostHS, USBH_HID_CLASS);
	  USBH_Start(&hUsbHostHS);
}

uint8_t taskHostProcess( struct mouseHID_t * m )
{
	HID_MOUSE_Info_TypeDef * mInfo;
	HID_TypeTypeDef type;
	USBH_Process( &hUsbHostHS );
	if ( Appli_state == APPLICATION_READY )
	{
		type = USBH_HID_GetDeviceType( &hUsbHostHS );
		if ( type == HID_MOUSE )
		{
			mInfo = USBH_HID_GetMouseInfo( &hUsbHostHS );
			if ( !mInfo )
				return 0;
			m->x = (*(int8_t *)&(mInfo->x));
			m->y = (*(int8_t *)&(mInfo->y));
			m->buttons = ( (mInfo->buttons[0]) ? 1 : 0 ) +
					     ( (mInfo->buttons[1]) ? 2 : 0 ) +
						 ( (mInfo->buttons[2]) ? 4 : 0 );
			adjustMouse( &(m->x), &(m->y) );
			return 1;
		}
	}
	return 0;
}

static void myUserProcess( USBH_HandleTypeDef *phost, uint8_t id )
{
  switch(id)
  {
  case HOST_USER_SELECT_CONFIGURATION:
	  break;

  case HOST_USER_DISCONNECTION:
	  Appli_state = APPLICATION_DISCONNECT;
	  break;

  case HOST_USER_CLASS_ACTIVE:
	  Appli_state = APPLICATION_READY;
	  break;

  case HOST_USER_CONNECTION:
	  Appli_state = APPLICATION_START;
	  break;

  default:
	  break;
  }
}


