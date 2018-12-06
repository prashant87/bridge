
#ifndef __CLASSIFIER_H_
#define __CLASSIFIER_H_

#include <vector>

/**
 * @brief The Classifier class
 * Default number of categories=3 engage, disengage and idle.
 */

class Classifier
{
public:
    Classifier();
    ~Classifier();

    void setProperties( float scale, float sigma, float dataSigma );
    void properties( float & scale, float & sigma, float & dataSigma );

    void dimensions( int & rawQty, int & stdQty, int & step );
    void setCategories( int categories = 3 );
    void push( int category, const std::vector<float> & data );
    int  classify( const std::vector<float> & data );

    bool save( const char * fname );
    bool load( const char * fname );

private:
    class PD;
    PD * pd;
};



#endif






