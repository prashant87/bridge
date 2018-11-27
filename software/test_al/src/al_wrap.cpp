
#include "al_wrap.h"
#include "al_stream.h"

#include <mutex>
#include <thread>
#include <chrono>
#include <functional>

#include <AL/al.h>
#include <AL/alc.h>



class AlWrap::PD
{
public:
    bool initialized;
    bool terminated;
    std::vector<AlStream *> streams;

    ALCdevice  * device;
    ALCcontext * context;
    ALuint frequency; // = 22050;
    ALenum format;    // = AL_FORMAT_MONO16;
    ALuint bufferSz;
    ALuint buffersQty;

    std::mutex  mutex;
    std::thread th;

    PD();
    ~PD();
};

AlWrap::PD::PD()
{
    initialized = false;
    terminated  = false;
    device      = 0;
    context     = 0;

    frequency  = 22050;
    format     = AL_FORMAT_MONO16;
    bufferSz   = 1024;
    buffersQty = 4;
}

AlWrap::PD::~PD()
{
    // Remove all streams.
    for ( std::vector<AlStream *>::const_iterator it=streams.begin();
          it!=streams.end(); it++ )
    {
        AlStream * stream = *it;
        delete stream;
    }
    streams.clear();

    if ( context )
    {
        device = alcGetContextsDevice( context );
        alcMakeContextCurrent( 0 );
        alcDestroyContext( context );
        alcCloseDevice( device );
    }
}


AlWrap::AlWrap()
{
    pd = new PD();
    pd->initialized = init();
    pd->th = std::thread( std::bind( &AlWrap::process, this ) );
}

AlWrap::~AlWrap()
{
    pd->terminated = true;
    pd->th.join();
    delete pd;
}

AlStream * AlWrap::createStream( StreamData * data )
{
    std::lock_guard<std::mutex> lg( pd->mutex );
        AlStream * st = new AlStream( pd->frequency, pd->format, pd->buffersQty, pd->bufferSz, data );
        pd->streams.push_back( st );
        return 0;
}

void AlWrap::removeStream( AlStream * stream )
{
    std::lock_guard<std::mutex> lg( pd->mutex );
        for ( std::vector<AlStream *>::const_iterator it=pd->streams.begin();
              it!=pd->streams.end(); it++ )
        {
            AlStream * st = *it;
            if ( stream == st )
            {
                pd->streams.erase( it );
                delete st;
                break;
            }
        }
}

bool AlWrap::init()
{
    // Verify that a given extension is available for the current context
    ALCboolean enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
    if (enumeration == AL_FALSE)
       return false;

    // Retrieve a list of available devices
    // Each device name is separated by a single NULL character
    // and the list is terminated with 2 NULL characters
    const ALCchar * deviceNameList = alcGetString( NULL, ALC_DEVICE_SPECIFIER );

    // Retrieve the default device name
    const ALCchar * defaultDeviceName = alcGetString( NULL, ALC_DEFAULT_DEVICE_SPECIFIER );

    // Open the default device
    pd->device = alcOpenDevice(defaultDeviceName);
    if ( !pd->device )
        return false;

    // Create context
    pd->context = alcCreateContext( pd->device, 0 );
    if ( pd->context == 0 )
    {
        alcCloseDevice( pd->device );
        pd->device = 0;
        return false;
    }

    // Set active context
    if ( !alcMakeContextCurrent( pd->context ) )
    {
       alcDestroyContext( pd->context );
       alcCloseDevice( pd->device );
       pd->context = 0;
       pd->device  = 0;

       return false;
    }

    return true;
}

void AlWrap::process()
{
    const int DELAY_MS = 5;
    std::vector<AlStream *> streams;
    while ( !pd->terminated )
    {
        std::this_thread::sleep_for( std::chrono::milliseconds( DELAY_MS ) );
        // Copy list of sound streams in protected environment.
        std::lock_guard<std::mutex> lg( pd->mutex );
            streams = pd->streams;
            // Parse each one and play it.
            for ( std::vector<AlStream *>::const_iterator it=streams.begin();
                  it!=streams.end(); it++ )
            {
                AlStream * stream = *it;
                stream->processBuffers();
            }
    }
}





