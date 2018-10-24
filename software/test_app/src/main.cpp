
#include <iostream>
#include <iomanip>
#include "io.h"

int main( int argc, char * argv[] )
{
    const int QTY = 5;
    IoData data[QTY];
    Io io;


    for ( ;; )
    {
        const int qty = io.read( data, QTY );
        if ( qty > 0 )
        {
            std::cout << "###############" << std::endl;
            std::cout << "qty: qty" << std::endl;
            for ( int i=0; i<qty; i++ )
            {
                const IoData & d = data[i];
                for ( int j=0; j<7; j++ )
                    std::cout << " " << std::setw( 5 ) << d.v[j];
                std::cout << std::endl;
            }
        }
        else

    }

    return 0;
}

