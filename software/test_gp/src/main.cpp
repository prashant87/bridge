
#include <iostream>
#include <cmath>
#include <random>
#include "gaussian_process_regression.h"

const int INPUTS  = 10;
const int OUTPUTS = 1;

const int TRAIN   = 1000;
const int TEST    = 20;

std::mt19937 gen(0);
std::uniform_real_distribution<> distA(-1.0, 1.5);
std::uniform_real_distribution<> distB(0.0, 2.0);

typedef Eigen::Matrix<float, INPUTS, 1>  IN;
typedef Eigen::Matrix<float, OUTPUTS, 1> OUT;

void generateSample( int n, IN & in, OUT & out );


int main( int argc, char * argv[] )
{
    GaussianProcessRegression<float> gpr(INPUTS, OUTPUTS);
    gpr.SetHyperParams( 1.1, 1.0, 0.4 );

    IN  in;
    OUT out;

    // Training.
    for ( int i=0; i<TRAIN; i++ )
    {
        int n = i%2;
        generateSample( n, in, out );
        gpr.AddTrainingData( in, out );
    }

    // Testing.
    for ( int i=0; i<TEST; i++ )
    {
        int n = i%2;
        generateSample( n, in, out );
        out = gpr.DoRegression( in );
        std::cout << "class: " << n << ", predicted: " << out(0) << std::endl;
    }






    return 0;
}

void generateSample( int n, IN & in, OUT & out )
{
    for ( int i=0; i<INPUTS; i++ )
    {
        if ( n < 1 )
            in(i) = distA(gen);
        else
            in(i) = distB(gen);
    }
    if ( n < 1 )
        out(0) = 1.0;
    else
        out(0) = 2.0;
}



