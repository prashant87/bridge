
#ifndef __PLOT_MAKER_H_
#define __PLOT_MAKER_H_

#include "io.h"
#include <vector>

// Dirty include right into the header.
#include <chrono>
#include <thread>
#include <mutex>

const int PLOT_QTY = 7;

struct PlotData
{
    std::vector<float> data;
    int currentIndex;
};

class PlotMaker
{
public:
    PlotMaker();
    ~PlotMaker();

    void setLength( int qty );
    void array( int index, std::vector<float> & data );

private:
    void process();

    std::thread th;
    std::mutex  mutex;
    bool terminated;

    int qty;
    PlotData data[7];
};




#endif



