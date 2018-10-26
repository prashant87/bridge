
#include "plot_maker.h"

PlotMaker::PlotMaker()
{
    setLength( 1024 );

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

