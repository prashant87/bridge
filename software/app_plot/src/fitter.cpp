
#include "fitter.h"
#include "gaussian_process_regression.h"

#include "portable_iarchive.hpp"
#include "portable_oarchive.hpp"
#include <fstream>

#include <Eigen/Dense>

// Right now have 3 channels. So "INPUTS" value should be a multiple of 3.
const int CHANNELS = 5;
const int RAW_READINGS_QTY = 10;
const int STD_READINGS_QTY = 10;
const int INPUTS  = CHANNELS*(RAW_READINGS_QTY + STD_READINGS_QTY);
const int OUTPUTS = 1;
const int STEP_SIZE = 2;
const float ALPHA = 0.05f;
const float _1_ALPHA = (1.0f - ALPHA);

typedef Eigen::Matrix<float, INPUTS, 1>  IN;
typedef Eigen::Matrix<float, OUTPUTS, 1> OUT;


class Fitter::PD
{
public:
    GaussianProcessRegression<float> gpr;
    float y;

    PD()
        : gpr( INPUTS, OUTPUTS ),
          y( 0.0f )
    {}

    ~PD() {}
};






Fitter::Fitter()
{
    pd = new PD();

    setProperties( 1.1, 1.0, 0.4 );
}

Fitter::~Fitter()
{
    delete pd;
}

void  Fitter::setProperties( float scale, float sigma, float dataSigma )
{
    pd->gpr.SetHyperParams( scale, sigma, dataSigma );
}

void  Fitter::properties( float & scale, float & sigma, float & dataSigma )
{
    double x, y, z;
    pd->gpr.GetHyperParams( x, y, z );
    scale     = x;
    sigma     = y;
    dataSigma = z;
}

void  Fitter::dimensions( int & rawQty, int & stdQty, int & step )
{
    rawQty = RAW_READINGS_QTY;
    stdQty = STD_READINGS_QTY;
    step   = STEP_SIZE;
}

void  Fitter::push( float v, const std::vector<float> & data )
{
    IN  in;
    OUT out;
    for ( int i=0; i<INPUTS; i++ )
        in(i) = data[i];
    out(0) = v;
    pd->gpr.AddTrainingData( in, out );
}

float Fitter::classify( const std::vector<float> & data )
{
    IN    in;
    OUT   out;

    for ( int i=0; i<INPUTS; i++ )
        in(i) = data[i];

    out = pd->gpr.DoRegression( in );
    const float x = out(0);
    pd->y = _1_ALPHA*pd->y + ALPHA*x;

    return pd->y;
}

bool Fitter::save( const char * fname )
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

        const int readingsQty = pd->gpr.get_n_data();
        oa << readingsQty;
        if ( readingsQty > 0 )
        {
            const Matrix & dIn  = pd->gpr.get_input_data();
            const Matrix & dOut = pd->gpr.get_output_data();
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

        out.flush();
        out.close();
    } catch(...)
    {
        res = false;
    }
    return res;
}

bool Fitter::load( const char * fname )
{
    bool res = true;
    try {
        std::ifstream in( fname );
        eos::portable_iarchive ia( in, boost::archive::no_header );

        float scale, sigma, dataSigma;
        ia >> scale;
        ia >> sigma;
        ia >> dataSigma;

        setProperties( scale, sigma, dataSigma );

        pd->gpr.ClearTrainingData();
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
                pd->gpr.AddTrainingData( vIn, vOut );
            }
        }

    } catch(...)
    {
        res = false;
    }
    return res;
}


