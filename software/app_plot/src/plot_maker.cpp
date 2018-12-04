
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

    stdmin = -10.0;
    stdmax = 8152.0;
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
    dataAudio[ currentIndex ] = v;

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
    : StreamData()
{
    audioSource = 3;

    for ( int i=0; i<PLOT_QTY; i++ )
    {
        PlotData & d = data[i];
        d.init();
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

void PlotMaker::stdLimits( int index, float & vmin, float & vmax )
{
    const PlotData & d = this->data[index];
    vmin = d.stdmin;
    vmax = d.stdmax;
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

void PlotMaker::stdMoveUp( int index, float percent )
{
    PlotData & d = this->data[index];
    const float dv = (d.stdmax - d.stdmin) * percent / 100.0f;
    d.stdmax += dv;
    d.stdmin += dv;
}

void PlotMaker::stdMoveDown( int index, float percent )
{
    PlotData & d = this->data[index];
    const float dv = (d.stdmax - d.stdmin) * percent / 100.0f;
    d.stdmax -= dv;
    d.stdmin -= dv;
}

void PlotMaker::stdZoomIn( int index, float percent )
{
    PlotData & d = this->data[index];
    const float mv = (d.stdmax + d.stdmin) * 0.5f;
    const float dv = (d.stdmax - d.stdmin) * (100.0f - percent) / 100.0f * 0.5f;
    d.stdmax = mv + dv;
    d.stdmin = mv - dv;
}

void PlotMaker::stdZoomOut( int index, float percent )
{
    PlotData & d = this->data[index];
    const float mv = (d.stdmax + d.stdmin) * 0.5f;
    const float dv = (d.stdmax - d.stdmin) * (100.0f + percent) / 100.0f * 0.5f;
    d.stdmax = mv + dv;
    d.stdmin = mv - dv;
}


void PlotMaker::setAudioSource( int ind )
{
    audioSource = ind;
}

bool PlotMaker::samples( std::vector<unsigned short> & data )
{
    std::lock_guard<std::mutex> lg( mutex );
        PlotData & d = this->data[audioSource];
        const int sz = d.dataAudio.size();
        int qty = d.currentIndex - d.lastSoundIndex;
        if ( qty < 0 )
            qty += sz;
        data.resize( qty );
        for ( int i=0; i<qty; i++ )
        {
            int ind = d.lastSoundIndex + i;
            if ( ind >= sz )
                ind -= sz;
            const unsigned short v = d.dataAudio[ind];
            data[i] = v;
        }
        d.lastSoundIndex = d.currentIndex;
        return true;
}

void PlotMaker::classificationSample( int rawQty, int stdQty, int step, std::vector<float> & data )
{
    const int CHANNELS_QTY = 3;
    const int CHANNELS[] = { 3, 4, 5 };
    const int qty = CHANNELS_QTY*(rawQty + stdQty);
    data.resize( qty );
    int destInd = 0;
    for ( int i=0; i<CHANNELS_QTY; i++ )
    {
        PlotData & d = this->data[i];
        const int qty = (int)d.data.size();
        for ( int j=0; j<rawQty; j++ )
        {
            int ind = d.currentIndex - step*j;
            if ( ind < 0 )
                ind += qty;
            const float v = d.data[ind] / 65535.0;
            data[destInd++] = v;
        }
        for ( int j=0; j<stdQty; j++ )
        {
            int ind = d.currentIndex - step*j;
            if ( ind < 0 )
                ind += qty;
            const float v = d.dataStd[ind] / 65535.0;
            data[destInd++] = v;
        }
    }
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

