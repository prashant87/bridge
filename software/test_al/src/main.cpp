
#include <AL/al.h>
#include <AL/alc.h>


int main( int argc, char * argv[] )
{
    // ******************************************************
    //             Step 1: open a default audio device
    // ******************************************************

    // Verify that a given extension is available for the current context
    ALCboolean enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
    if (enumeration == AL_FALSE)
    {
       return -1;
    }

    // Retrieve a list of available devices
    // Each device name is separated by a single NULL character
    // and the list is terminated with 2 NULL characters
    const ALCchar * deviceNameList = alcGetString( NULL, ALC_DEVICE_SPECIFIER );

    // Retrieve the default device name
    const ALCchar * defaultDeviceName = alcGetString( NULL, ALC_DEFAULT_DEVICE_SPECIFIER );

    // Open the default device
    ALCdevice * device = alcOpenDevice(defaultDeviceName);
    if ( !device )
    {

       return -2;
    }


    // *****************************************************
    //             Step 2: create context
    // *****************************************************
    // Create context
    ALCcontext * context = alcCreateContext( device, NULL );
    if ( context == NULL )
    {
       alcCloseDevice(device);

       return -3;
    }

    // Set active context
    if ( !alcMakeContextCurrent( context ) )
    {
       alcDestroyContext( context );
       alcCloseDevice( device );

       return -4;
    }



    // ***********************************************************
    //           Step 3: create source and set it's parameters
    // ***********************************************************
    ALuint source;
    // Request a source name
    alGenSources( (ALuint)1, &source );

    // Set the default volume
    alSourcef( source, AL_GAIN, 1 );

    // Set the default position of the sound
    alSource3f( source, AL_POSITION, 0, 0, 0 );



    // ***********************************************************
    //           Step 4: create buffers
    // ***********************************************************
    ALuint buffer[4];
    // Request a buffer name
    alGenBuffers(1, &buffer);

    const ALuint frequency = 22050;
    const ALenum format = AL_FORMAT_MONO16;


    // Fill all the buffers with audio data from the wave file
    for ( int iLoop = 0; iLoop < 4; iLoop++ )
    {
       alBufferData( buffer[iLoop], format, pData, DATA_CHUNK_SIZE, frequency );
       alSourceQueueBuffers( source, 1, &buffer[iLoop] );
    }









    // Start playing the streamed audio
    alSourcePlay(source);
    LOGI("[%s] alSourcePlay", __func__);

    // Buffer queuing loop must operate in a new thread
    iBuffersProcessed = 0;
    while (!thread_finish)
    {
       usleep(10 * 1000); // Sleep 10 msec periodically

       alGetSourcei(source, AL_BUFFERS_PROCESSED, &iBuffersProcessed);

       iTotalBuffersProcessed += iBuffersProcessed;
       ALOGI("Buffers Processed %d", iTotalBuffersProcessed);

       // For each processed buffer, remove it from the source queue, read the next chunk of
       // audio data from the file, fill the buffer with new data, and add it to the source queue
       while (iBuffersProcessed)
       {
          // Remove the buffer from the queue (uiBuffer contains the buffer ID for the dequeued buffer)
          uiBuffer = 0;
          alSourceUnqueueBuffers(source, 1, &uiBuffer);

          // Read more pData audio data (if there is any)

          // Copy audio data to buffer
          alBufferData(uiBuffer, AL_FORMAT_MONO16, pData, DATA_CHUNK_SIZE, 22050);
          // Insert the audio buffer to the source queue
          alSourceQueueBuffers(source, 1, &uiBuffer);

          iBuffersProcessed--;
       }
    }



    // Cleanup.
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    device = alcGetContextsDevice(context);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);

    return 0;
}


