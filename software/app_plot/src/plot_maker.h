
#ifndef __PLOT_MAKER_H_
#define __PLOT_MAKER_H_

#include "io.h"
#include "al_wrap.h"

#include <vector>

// Dirty include right into the header.
#include <chrono>
#include <thread>
#include <mutex>

const int PLOT_QTY = 7;

struct PlotData
{
    std::vector<float> data;
    float vmin,   vmax,
          stdmin, stdmax;
    int currentIndex;
    int lastSoundIndex;

    // For analysis.
    float alpha;
    float mean;
    float std;
    std::vector<float> dataStd;

    std::vector<unsigned short> dataAudio;

    void init();
    void setLength( int qty );
    void push( unsigned short v );
};

class PlotMaker: public StreamData
{
public:
    PlotMaker();
    ~PlotMaker();

    void setLength( int qty );
    void array( int index, std::vector<float> & data );
    void arrayStd( int index, std::vector<float> & dataStd );
    void limits( int index, float & vmin, float & vmax );
    void stdLimits( int index, float & vmin, float & vmax );

    void moveUp( int index, float percent = 20.0 );
    void moveDown( int index, float percent = 20.0 );
    void zoomIn( int index, float percent = 20.0 );
    void zoomOut( int index, float percent = 20.0 );

    void stdMoveUp( int index, float percent = 20.0 );
    void stdMoveDown( int index, float percent = 20.0 );
    void stdZoomIn( int index, float percent = 20.0 );
    void stdZoomOut( int index, float percent = 20.0 );

    void setAudioSource( int ind );
    bool samples(std::vector<unsigned short> & data ) override;

    void classificationSample( int rawQty, int stdQty, int step, std::vector<float> & data );

private:
    void process();

    std::thread th;
    std::mutex  mutex;
    bool terminated;

    int qty;
    int audioSource;
    PlotData data[7];
};




#endif



