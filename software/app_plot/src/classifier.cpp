
#include "classifier.h"
#include "gaussian_process_regression.h"

// Right now have 3 channels. So "INPUTS" value should be a multiple of 3.
const int CHANNELS = 3;
const int RAW_READINGS_QTY = 5;
const int STD_READINGS_QTY = 5;
const int INPUTS  = CHANNELS*(RAW_READINGS_QTY + STD_READINGS_QTY);
const int OUTPUTS = 1;
const int STEP_SIZE = 10;

typedef Eigen::Matrix<float, INPUTS, 1>  IN;
typedef Eigen::Matrix<float, OUTPUTS, 1> OUT;


struct OneClassifier
{
    GaussianProcessRegression<float> gpr;

    OneClassifier()
        : gpr( INPUTS, OUTPUTS )
    {}
};


class Classifier::PD
{
public:
    std::vector<OneClassifier> classifiers;

    void setCategories( int qty=3 );
    PD();
    ~PD();
};

void Classifier::PD::setCategories( int qty )
{
    classifiers.resize( qty );
}

Classifier::PD::PD()
{
    setCategories( 3 );
}

Classifier::PD::~PD()
{

}




Classifier::Classifier()
{
    pd = new PD();
}

Classifier::~Classifier()
{
    delete pd;
}

void Classifier::dimensions( int & rawQty, int stdQty, int & step )
{
    rawQty = RAW_READINGS_QTY;
    stdQty = STD_READINGS_QTY;
    step   = STEP_SIZE;
}

void Classifier::setCategories( int categories )
{
    pd->setCategories( categories );
}

void Classifier::push( int category, const std::vector<float> & data )
{
    IN  in;
    OUT out;
    for ( int i=0; i<INPUTS; i++ )
        in(i) = data[i];
    const int qty = (int)pd->classifiers.size();
    for ( int i=0; i<qty; i++ )
    {
        out(0) = (i==category) ? 1.0f : 0.0f;
        pd->classifiers[i].gpr.AddTrainingData( in, out );
    }
}

int  Classifier::classify( const std::vector<float> & data )
{
    float val;
    int   ind = -1;
    IN    in;
    OUT   out;

    for ( int i=0; i<INPUTS; i++ )
        in(i) = data[i];
    const int qty = (int)pd->classifiers.size();
    for ( int i=0; i<qty; i++ )
    {
        out = pd->classifiers[i].gpr.DoRegression( in );
        const float v = out(0);
        if ( ( i==0 ) || ( v > val ) )
        {
            val = v;
            ind = i;
        }
    }

    return ind;
}



