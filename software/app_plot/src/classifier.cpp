
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
}

Classifier::~Classifier()
{
    delete pd;
}

void Classifier::dimensions( int & rawQty, int & stdQty, int & step )
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

bool Classifier::save( const char * fname )
{
    typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> Matrix;
    typedef Eigen::Matrix<float, Eigen::Dynamic, 1>              Vector;

    bool res = true;
    try {
        std::ofstream out( fname );
        eos::portable_oarchive oa( out, boost::archive::no_header );

        const int qty = static_cast<int>( pd->classifiers.size() );
        oa << qty;

        for ( int i=0; i<qty; i++ )
        {
            OneClassifier & c = pd->classifiers[i];
            //const MatrixXr& get_input_data()  {return input_data_;};
            //const MatrixXr& get_output_data()  {return output_data_;};
            const Matrix & dIn  = c.gpr.get_input_data();
            const Vector & dOut = c.gpr.get_output_data();
            const int dims        = dIn.rows();
            const int readingsQty = dIn.rows();
            oa << dims;
            oa << readingsQty;
            for ( int j=0; j<readingsQty; j++ )
            {
                for ( int k=0; k<dims; k++ )
                {
                    const float v = dIn(j, k);
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

bool Classifier::load( const char * fname )
{
    bool res = true;
    try {
        std::ifstream in( fname );
        eos::portable_iarchive ia( in, boost::archive::no_header );

        int qty;
        ia >> qty;

        pd->classifiers.clear();
        pd->classifiers.resize( qty );

        for ( int i=0; i<qty; i++ )
        {
            OneClassifier & c = pd->classifiers[i];
            int dims;
            ia >> dims;
            int readingsQty;
            ia >> readingsQty;
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

    } catch(...)
    {
        res = false;
    }
    return res;
}




