
#include <iostream>
#include <iomanip>
#include "io.h"

#include <chrono>
#include <thread>

int main( int argc, char * argv[] )
{
    const int QTY = 4;
    IoData data[QTY];
    Io io;


    for ( ;; )
    {
        const int qty = io.read( data, QTY );
        std::cout << "###############" << std::endl;
        std::cout << "qty: " << qty << std::endl;
        if ( qty > 0 )
        {
            for ( int i=0; i<qty; i++ )
            {
                const IoData & d = data[i];
                for ( int j=0; j<7; j++ )
                    std::cout << " " << std::setw( 5 ) << d.v[j];
                std::cout << std::endl;
            }
        }
        else
        {
            // Sleep
            std::this_thread::sleep_for( std::chrono::milliseconds(1) );
        }
    }

    return 0;
}

