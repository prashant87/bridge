
#include "plot_maker.h"

PlotMaker::PlotMaker()
{
    setLength( 256 );

    for ( int i=0; i<PLOT_QTY; i++ )
    {
        PlotData & d = data[i];
        d.vmin = 32767.0f - 1000.0f;
        d.vmax = 32767.0f + 1000.0f;
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
            d.currentIndex = 0;
            d.data.resize( qty );
            for ( int j=0; j<qty; j++ )
                d.data[j] = 0.0f;
        }
}

void PlotMaker::array( int index, std::vector<float> & data )
{
    std::lock_guard<std::mutex> g( mutex );
        data = this->data[index].data;
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
                    d.data[ d.currentIndex ] = static_cast<float>( raw_data[n].v[i] );
                    d.currentIndex += 1;
                    if ( d.currentIndex >= this->qty )
                        d.currentIndex = 0;
                }
            }
    }
}

