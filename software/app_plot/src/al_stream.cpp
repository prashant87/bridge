
#include "al_stream.h"
#include <vector>
#include <iostream>

AlStream::AlStream( ALuint frequency, ALenum format, ALuint buffersQty, ALuint bufferSz, StreamData * streamData )
{
    val = 0.0f;

    this->freeBuffers = 0;

    this->streamData = streamData;
    this->frequency = frequency;
    this->format    = format;
    buffers.resize( buffersQty );
    data.resize( buffersQty * bufferSz );

    // Request a source name
    alGenSources( (ALuint)1, &source );

    // Set the default volume
    alSourcef( source, AL_GAIN, 1 );

    // Set the default position of the sound
    alSource3f( source, AL_POSITION, 0, 0, 0 );


    initBuffers();

    // Start playing the streamed audio
    alSourcePlay(source);
}

AlStream::~AlStream()
{
    ALuint buffersQty = buffers.size();
    alDeleteSources( 1, &source );
    alDeleteBuffers( buffersQty, &(buffers[0]) );
}

void AlStream::initBuffers()
{
    ALuint buffersQty = (ALuint)buffers.size();
    alGenBuffers(buffersQty, &(buffers[0]));
    ALuint bufferSz = (ALuint)data.size() / buffersQty;

    // Initilize data to middle value (for 16 bit it is 32767).
    std::size_t qty = data.size();
    for ( std::size_t j=0; j<qty; j++ )
        data[j] = 32767;

    // Fill all the buffers with audio data from the wave file
    for ( int i=0; i<buffersQty; i++ )
    {
        ALvoid * pData = (ALvoid *)&(data[i*bufferSz]);
        alBufferData( buffers[i], format, pData, bufferSz, frequency );
        alSourceQueueBuffers( source, 1, &buffers[i] );
    }
}

void AlStream::processBuffers()
{
    ALuint buffersQty = (ALuint)buffers.size();
    ALuint bufferSz = (ALuint)data.size() / buffersQty;

    ALint buffersProcessed;
    alGetSourcei(source, AL_BUFFERS_PROCESSED, &buffersProcessed);
    freeBuffers += buffersProcessed;

    //iTotalBuffersProcessed += iBuffersProcessed;
    //ALOGI("Buffers Processed %d", iTotalBuffersProcessed);

    // For each processed buffer, remove it from the source queue, read the next chunk of
    // audio data from the file, fill the buffer with new data, and add it to the source queue
    if ( freeBuffers > 0 )
    {
        // Remove the buffer from the queue (uiBuffer contains the buffer ID for the dequeued buffer)
        ALuint uiBuffer = 0;
        alSourceUnqueueBuffers(source, 1, &uiBuffer);

        ALvoid * pData = 0;
        short * usData = 0;
        // Find corresponding data buffer.
        for ( ALuint i=0; i<buffersQty; i++ )
        {
            ALuint bufferInd = buffers[i];
            if ( bufferInd == uiBuffer )
            {
                usData = &(data[bufferSz*i]);
                pData = (ALvoid *)&(data[bufferSz*i]);
                break;
            }
        }
        if ( pData == 0 )
            return;

        // Read more pData audio data (if there is any).
        if ( !streamData->samples( rawData ) )
            return;

        const ALuint qty = (ALuint)rawData.size();
        float alpha = (float)qty / (float)bufferSz * 2.0f;// * 5.0;
        if ( alpha >= 0.9f )
            alpha = 0.9f;
        const float _1_alpha = 1.0f - alpha;
        for ( ALuint i=0; i<bufferSz; i++ )
        {
            if ( qty > 0 )
            {
                const ALuint rawInd = qty * i / bufferSz;
                const float v = (float)rawData[rawInd] - 32767.0f;
                val = (alpha * v + _1_alpha * val);
                const short uv = (short)(val);
                usData[i] = uv; // ((uv & 0x00FF) << 8) |
                                // ((uv & 0xFF00) >> 8);
            }
            else
                usData[i] = (short)0;
        }

        // Copy audio data to buffer
        alBufferData( uiBuffer, format, pData, bufferSz, frequency );
        // Insert the audio buffer to the source queue
        alSourceQueueBuffers(source, 1, &uiBuffer);

        // Check if playing or not and force play if needed.
        ALint state;
        alGetSourcei( source, AL_SOURCE_STATE, &state );
        if ( state != AL_PLAYING )
            alSourcePlay( source );

        // Decrease number of free buffers.
        freeBuffers -= 1;

        //std::cout << "a" << std::endl;
    }
}






