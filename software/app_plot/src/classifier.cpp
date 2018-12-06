
#include "classifier.h"
#include "gaussian_process_regression.h"

#include "portable_iarchive.hpp"
#include "portable_oarchive.hpp"
#include "portable_insts.hpp"
#include <fstream>

#include <Eigen/Dense>

// Right now have 3 channels. So "INPUTS" value should be a multiple of 3.
const int CHANNELS = 3;
const int RAW_READINGS_QTY = 5;
const int STD_READINGS_QTY = 5;
const int INPUTS  = CHANNELS*(RAW_READINGS_QTY + STD_READINGS_QTY);
const int OUTPUTS = 1;
const int STEP_SIZE = 50;

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

    setProperties( 1.1, 1.0, 0.4 );
}

Classifier::~Classifier()
{
    delete pd;
}

void Classifier::setProperties( float scale, float sigma, float dataSigma )
{
    const size_t qty = pd->classifiers.size();
    for ( size_t i=0; i<qty; i++ )
    {
        OneClassifier & c = pd->classifiers[i];
        c.gpr.SetHyperParams( scale, sigma, dataSigma );
    }
}

void Classifier::properties( float & scale, float & sigma, float & dataSigma )
{
    const size_t qty = pd->classifiers.size();
    if ( qty > 0 )
    {
        OneClassifier & c = pd->classifiers[0];
        double x, y, z;
        c.gpr.GetHyperParams( x, y, z );
        scale     = x;
        sigma     = y;
        dataSigma = z;
    }
    else
    {
        scale = -1.0;
        sigma = -1.0;
        dataSigma = -1.0;
    }
}

void Classifier::dimensions( int & rawQty, int & stdQty, int & step )
{
    rawQty = RAW_READINGS_QTY;
    stdQty = STD_READINGS_QTY;
    step   = STEP_SIZE;
}

void Classifier::setCategories( int categories )
{
    float scale, sigma, dataSigma;
    properties( scale, sigma, dataSigma );

    pd->setCategories( categories );

    setProperties( scale, sigma, dataSigma );
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

bool Classifier::save( const char * fname )
{
    typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> Matrix;
    typedef Eigen::Matrix<float, Eigen::Dynamic, 1>              Vector;

    bool res = true;
    try {
        std::ofstream out( fname );
        eos::portable_oarchive oa( out, boost::archive::no_header );

        float scale, sigma, dataSigma;
        properties( scale, sigma, dataSigma );
        oa << scale;
        oa << sigma;
        oa << dataSigma;

        const int qty = static_cast<int>( pd->classifiers.size() );
        oa << qty;

        for ( int i=0; i<qty; i++ )
        {
            OneClassifier & c = pd->classifiers[i];
            //const MatrixXr& get_input_data()  {return input_data_;};
            //const MatrixXr& get_output_data()  {return output_data_;};
            const int readingsQty = c.gpr.get_n_data();
            oa << readingsQty;
            if ( readingsQty > 0 )
            {
                const Matrix & dIn  = c.gpr.get_input_data();
                const Matrix & dOut = c.gpr.get_output_data();
                const int dims      = dIn.rows();
                oa << dims;
                for ( int j=0; j<readingsQty; j++ )
                {
                    for ( int k=0; k<dims; k++ )
                    {
                        const float v = dIn(k, j);
                        oa << v;
                    }
                    const float v = dOut(j);
                    oa << v;
                }
            }
        }

        out.flush();
        out.close();
    } catch(...)
    {
        res = false;
    }
    return res;
}

bool Classifier::load( const char * fname )
{
    bool res = true;
    try {
        std::ifstream in( fname );
        eos::portable_iarchive ia( in, boost::archive::no_header );

        float scale, sigma, dataSigma;
        ia >> scale;
        ia >> sigma;
        ia >> dataSigma;

        int qty;
        ia >> qty;

        pd->classifiers.clear();
        pd->classifiers.resize( qty );

        setProperties( scale, sigma, dataSigma );

        for ( int i=0; i<qty; i++ )
        {
            OneClassifier & c = pd->classifiers[i];
            c.gpr.ClearTrainingData();
            int readingsQty;
            ia >> readingsQty;
            if ( readingsQty > 0 )
            {
                int dims;
                ia >> dims;
                Eigen::Matrix<float, Eigen::Dynamic, 1> vIn;
                Eigen::Matrix<float, 1, 1> vOut;
                vIn.resize( dims, 1 );
                for ( int j=0; j<readingsQty; j++ )
                {
                    for ( int k=0; k<dims; k++ )
                    {
                        float v;
                        ia >> v;
                        vIn(k) = v;
                    }
                    float v;
                    ia >> v;
                    vOut(0) = v;
                    c.gpr.AddTrainingData( vIn, vOut );
                }
            }
        }

    } catch(...)
    {
        res = false;
    }
    return res;
}




