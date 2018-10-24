
set( proj "io" )

#include( "${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindUSB1.cmake" )
#find_package( USB1 REQUIRED )
include( "${CMAKE_CURRENT_SOURCE_DIR}/cmake/findlibusb-1.0.cmake" )
message( STATUS ${LIBUSB_1_DEFINITIONS} )

include_directories( "./src" 
                     ${LIBUSB_1_INCLUDE_DIRS} 
                   )

file( GLOB src "./src/*.cpp" )
set( libs ${LIBUSB_1_LIBRARIES} )

add_library( ${proj} STATIC ${src} )
target_link_libraries( ${proj} ${libs} )







