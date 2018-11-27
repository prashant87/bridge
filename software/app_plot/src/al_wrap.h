
#ifndef __AL_WRAP_H_
#define __AL_WRAP_H_

#include <vector>

class AlStream;

class StreamData
{
public:
    StreamData() {}
    virtual ~StreamData() {}
    virtual bool samples( std::vector<unsigned short> & data ) = 0;
};

class AlWrap
{
public:
    AlWrap();
    virtual ~AlWrap();

    AlStream * createStream( StreamData * data );
    void removeStream( AlStream * stream );

protected:
    bool init();
    void process();

    class PD;
    PD * pd;
};



#endif



