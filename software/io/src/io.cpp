
#include "io.h"
#include <libusb-1.0/libusb.h>

#define VENDOR_ID  0x1234
#define PRODUCT_ID 0x5678

#define EP_IN 0x81
#define TIMEOUT 10
#define RETRIES 10

class Io::PD
{
public:
    libusb_device_handle * dev;
    int retries;

    PD();
    ~PD();

    void close();
    bool open();
    bool isOpen() const;
    int  read( IoData * data, int maxQty );
};

Io::PD::PD()
{
    dev     = 0;
    retries = 0;
    int rc = libusb_init( 0 );
    libusb_set_debug( 0, 3 );
}

Io::PD::~PD()
{
    close();
}

void Io::PD::close()
{
    if ( dev )
    {
        libusb_close( dev );
        dev = 0;
    }
}

bool Io::PD::open()
{
    if ( dev )
        close();
    dev = libusb_open_device_with_vid_pid( 0, 
                        VENDOR_ID, PRODUCT_ID );
    if ( !dev )
        return false;

    for ( int itf=0; itf<2; itf++ )
    {
        if ( libusb_kernel_driver_active( dev, itf ) )
            libusb_detach_kernel_driver( dev, itf );
        int rc = libusb_claim_interface( dev, itf );
        if ( rc < 0 )
        {
            close();
            return false;
        }
    }

    retries = 0;
    return true;
}

bool Io::PD::isOpen() const
{
    const bool opened = (dev != 0);
    return opened;
}

int  Io::PD::read( IoData * data, int maxQty )
{
    if ( retries >= RETRIES )
        close();
    const bool is_open = isOpen();
    if ( !is_open )
    {
        const bool opened = open();
        if ( !opened )
            return false;
    }

    int actual_length;
    unsigned char * d = reinterpret_cast<unsigned char *>( data );
    const int sz = maxQty * sizeof( IoData );
    int rc = libusb_bulk_transfer( dev, EP_IN, d, sz, &actual_length, TIMEOUT );
    if ( rc <= 0 )
    {
        retries += 1;
        return rc;
    }

    int qty = actual_length / sizeof( IoData );

    return qty;


}





