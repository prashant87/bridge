
#include "plot_maker.h"
#include <cmath>

void PlotData::init()
{
    alpha = 0.01;
    mean  = 0.0f;
    std   = 0.0f;
    setLength( 2048 );
    vmin = 32767.0f - 32767.0f;
    vmax = 32767.0f + 32767.0f;
}

void PlotData::setLength( int qty )
{
    PlotData & d = *this;
    d.currentIndex = 0;
    d.lastSoundIndex = 0;
    d.data.resize( qty );
    d.dataStd.resize( qty );
    d.dataAudio.resize( qty );
    for ( int j=0; j<qty; j++ )
    {
        d.dataStd[j] = d.data[j] = 0.0f;
        d.dataAudio[j] = 32767;
    }
}

void PlotData::push( unsigned short v )
{
    const int qty = static_cast<int>( data.size() );

    const float f = static_cast<float>( v );
    data[ currentIndex ] = f;

    const float _1_alpha = 1.0f - alpha;
    mean = _1_alpha*mean + alpha*f;
    const float d = std::abs( f - mean );
    std  = _1_alpha*std + alpha*d;

    dataStd[ currentIndex ] = std;

    currentIndex += 1;
    if ( currentIndex >= qty )
        currentIndex = 0;

}


PlotMaker::PlotMaker()
{
    audioSource = 4;

    for ( int i=0; i<PLOT_QTY; i++ )
    {
        PlotData & d = data[i];
        d.setLength( 2048 );
    }

    terminated = false;
    th = std::thread( &PlotMaker::process, this );
}

PlotMaker::~PlotMaker()
{
    terminated = true;
    th.join();
}

void PlotMaker::setLength( int qty )
{
    std::lock_guard<std::mutex> g( mutex );
        this->qty = qty;
        for ( int i=0; i<PLOT_QTY; i++ )
        {
            PlotData & d = data[i];
            d.setLength( qty );
        }
}

void PlotMaker::array( int index, std::vector<float> & data )
{
    std::lock_guard<std::mutex> g( mutex );
        data = this->data[index].data;
}

void PlotMaker::arrayStd( int index, std::vector<float> & dataStd )
{
    std::lock_guard<std::mutex> g( mutex );
    dataStd = this->data[index].dataStd;
}

void PlotMaker::limits( int index, float & vmin, float & vmax )
{
    const PlotData & d = this->data[index];
    vmin = d.vmin;
    vmax = d.vmax;
}

void PlotMaker::moveUp( int index, float percent )
{
    PlotData & d = this->data[index];
    const float dv = (d.vmax - d.vmin) * percent / 100.0f;
    d.vmax += dv;
    d.vmin += dv;
}

void PlotMaker::moveDown( int index, float percent )
{
    PlotData & d = this->data[index];
    const float dv = (d.vmax - d.vmin) * percent / 100.0f;
    d.vmax -= dv;
    d.vmin -= dv;
}

void PlotMaker::zoomIn( int index, float percent )
{
    PlotData & d = this->data[index];
    const float mv = (d.vmax + d.vmin) * 0.5f;
    const float dv = (d.vmax - d.vmin) * (100.0f - percent) / 100.0f * 0.5f;
    d.vmax = mv + dv;
    d.vmin = mv - dv;
}

void PlotMaker::zoomOut( int index, float percent )
{
    PlotData & d = this->data[index];
    const float mv = (d.vmax + d.vmin) * 0.5f;
    const float dv = (d.vmax - d.vmin) * (100.0f + percent) / 100.0f * 0.5f;
    d.vmax = mv + dv;
    d.vmin = mv - dv;
}

void PlotMaker::setAudioSource( int ind )
{
    audioSource = ind;
}

bool PlotMaker::samples( std::vector<unsigned int> & data )
{
    PlotData & d = this->data[audioIndex];
    int qty = d.currentIndex - d.lastSoundIndex - 1;
    if ( qty < 0 )
        qty += (int)d.dataAudio.size();
    return true;
}


void PlotMaker::process()
{
    const int QTY = 4;
    IoData raw_data[QTY];
    Io io;

    while ( !terminated )
    {
        const int qty = io.read( raw_data, QTY );
        if ( qty <= 0 )
        {
            // Sleep
            std::this_thread::sleep_for( std::chrono::milliseconds(1) );
            continue;
        }

        std::lock_guard<std::mutex> g( mutex );
            for ( int n=0; n<qty; n++ )
            {
                for ( int i=0; i<PLOT_QTY; i++ )
                {
                    PlotData & d = data[i];
                    /*d.data[ d.currentIndex ] = static_cast<float>( raw_data[n].v[i] );
                    d.currentIndex += 1;
                    if ( d.currentIndex >= this->qty )
                        d.currentIndex = 0;*/
                    d.push( raw_data[n].v[i] );
                }
            }
    }
}

