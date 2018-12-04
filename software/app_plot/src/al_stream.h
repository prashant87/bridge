

#ifndef __AL_STREAM_H_
#define __AL_STREAM_H_

#include <vector>

#include <AL/al.h>
#include <AL/alc.h>

#include "al_wrap.h"

class AlStream
{
public:
    AlStream( ALuint frequency, ALenum format, ALuint buffersQty, ALuint bufferSz, StreamData * streamData );
    ~AlStream();

    void initBuffers();
    void processBuffers();

    StreamData * streamData;
    ALuint source;
    ALuint frequency;
    ALenum format;
    ALint  freeBuffers;
    std::vector<ALuint> buffers;
    std::vector<short> data;

    float val;
    std::vector<unsigned short> rawData;

};




#endif




