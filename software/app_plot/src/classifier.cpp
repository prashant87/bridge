
#include "classifier.h"
#include "gaussian_process_regression.h"

const int INPUTS  = 10;
const int OUTPUTS = 1;

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



