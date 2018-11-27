

#ifndef __AL_STREAM_H_
#define __AL_STREAM_H_

#include <AL/al.h>
#include <AL/alc.h>

#include "al_wrap.h"

class AlStream
{
public:
    AlStream( ALuint frequency, ALenum format, ALuint buffersQty, ALuint bufferSz, StreamData * data );
    ~AlStream();

    ALuint source;
    ALuint * buffers;

};




#endif




