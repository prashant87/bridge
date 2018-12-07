
#ifndef __FITTER_H_
#define __FITTER_H_

#include <vector>

/**
 * @brief The Fitter class
 */

class Fitter
{
public:
    Fitter();
    ~Fitter();

    void  setProperties( float scale, float sigma, float dataSigma );
    void  properties( float & scale, float & sigma, float & dataSigma );

    void  dimensions( int & rawQty, int & stdQty, int & step );
    void  push( float v, const std::vector<float> & data );
    float classify( const std::vector<float> & data );

    bool save( const char * fname );
    bool load( const char * fname );

private:
    class PD;
    PD * pd;
};






#endif




