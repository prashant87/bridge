
#include <iostream>
#include <cmath>
#include <random>
#include "gaussian_process_regression.h"

const int INPUTS  = 2;
const int OUTPUTS = 1;

const int TRAIN   = 10;
const int TEST    = 3;

typedef Eigen::Matrix<float, INPUTS, 1>  IN;
typedef Eigen::Matrix<float, OUTPUTS, 1> OUT;

void generateSample( int n, IN & in, OUT & out );


int main( int argc, char * argv[] )
{

    GaussianProcessRegression<float> gpr(INPUTS, OUTPUTS);
    gpr.SetHyperParams( 1.1, 1.0, 0.4 );

    for ( int i=0; i<TRAIN; i++ )
    {

    }

    for ( int i=0; i<TEST; i++ )
    {

    }






    return 0;
}



