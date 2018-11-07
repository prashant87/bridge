
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


    const int N = 10000;
    int n = 0;
    auto t_start = std::chrono::steady_clock::now();
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
            n += qty;
        }
        else
        {
            // Sleep
            std::this_thread::sleep_for( std::chrono::milliseconds(30) );
        }

        if ( n > N )
        {
            const auto t_end = std::chrono::steady_clock::now();
            std::chrono::duration<double, std::micro> duration = ( t_end - t_start );
            double dt = static_cast<double>( duration.count() );
            double nps = static_cast<double>( n ) / dt * 1.0e6;
            std::cout << "readings per second: " << nps << std::endl;

            n = 0;
            t_start = t_end;
        }
    }

    return 0;
}

