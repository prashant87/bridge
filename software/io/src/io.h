
#ifndef __IO_H_
#define __IO_H_


struct IoData
{
    unsigned short v[7];
};

class Io
{
public:
    Io();
    ~Io();

    int read( IoData * data, int maxQty );
private:
    class PD;
    PD * pd;
};



#endif




