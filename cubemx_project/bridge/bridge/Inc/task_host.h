
#ifndef __TASK_HOST_H_
#define __TASK_HOST_H_

#include <stdio.h>

struct mouseHID_t;

void    taskHostInit( void );
uint8_t taskHostProcess( struct mouseHID_t * m );




#endif

