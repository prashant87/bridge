
#include "al_wrap.h"
#include <thread>
#include <chrono>

class Stream: public StreamData
{
public:
    Stream();
    ~Stream();
    bool samples( std::vector<unsigned short> & data ) override;
};

int main( int argc, char * argv[] )
{
    AlWrap wrap;
    Stream st;

    AlStream * stream = wrap.createStream( &st );

    while ( true )
        std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );

    return 0;
}





Stream::Stream()
    : StreamData()
{

}

Stream::~Stream()
{

}

bool Stream::samples( std::vector<unsigned short> & data )
{
    const size_t SZ = 8;
    data.resize( SZ );
    for ( size_t i=0; i<SZ; i++ )
    {
        data[i] = ( i % 2 ) * 65535;
    }
    return true;
}

