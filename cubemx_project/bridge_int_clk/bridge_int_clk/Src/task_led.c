/*
 * task_led.c
 *
 *  Created on: Jul 4, 2018
 *      Author: z80
 */

#include "task_led.h"
#include "cmsis_os.h"
#include "gpio.h"

#define LED_PORT GPIOA
#define LED_0    GPIO_PIN_6
#define LED_1    GPIO_PIN_7

// Dimensions the buffer that the task being created will use as its stack.
// NOTE:  This is the number of words the stack will hold, not the number of
// bytes.  For example, if each stack item is 32-bits, and this is set to 100,
// then 400 bytes (100 * 32-bits) will be allocated.
#define LED_STACK_SIZE 200

// Structure that will hold the TCB of the task being created.
static StaticTask_t xTaskBuffer;

// Buffer that the task being created will use as its stack.  Note this is
// an array of StackType_t variables.  The size of StackType_t is dependent on
// the RTOS port.
static StackType_t xStack[ LED_STACK_SIZE ];

// Function that implements the task being created.
static void vTaskLed( void * pvParameters )
{
	// The parameter value is expected to be 1 as 1 is passed in the
	// pvParameters value in the call to xTaskCreateStatic().
	//configASSERT( ( uint32_t ) pvParameters == 1UL );

	for( ;; )
	{
		// Task code goes here.
		HAL_GPIO_WritePin( LED_PORT, LED_0 | LED_1, GPIO_PIN_SET );
		osDelay( 500 );
		HAL_GPIO_WritePin( LED_PORT, LED_0 | LED_1, GPIO_PIN_RESET );
		osDelay( 500 );
	}
}

// Function that creates a task.
void taskLedInit( void )
{
	//TaskHandle_t xHandle = NULL;

	// Create the task without using any dynamic memory allocation.
	/*xHandle = xTaskCreateStatic(
				  vTaskCode,       // Function that implements the task.
				  "NAME",          // Text name for the task.
				  STACK_SIZE,      // Stack size in words, not bytes.
				  ( void * ) 1,    // Parameter passed into the task.
				  tskIDLE_PRIORITY,// Priority at which the task is created.
				  xStack,          // Array to use as the task's stack.
				  &xTaskBuffer );  // Variable to hold the task's data structure.
	*/
	// puxStackBuffer and pxTaskBuffer were not NULL, so the task will have
	// been created, and xHandle will be the task's handle.  Use the handle
	// to suspend the task.
	//vTaskSuspend( xHandle );

	//osThreadCreate( vTaskLed, NULL );
	osThreadDef(ledTask, vTaskLed, osPriorityNormal, 0, 128);
	osThreadCreate(osThread(ledTask), NULL);
}

