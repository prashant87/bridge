
set( proj "io" )

include "./cmake/FindUSB1.cmake"
find_package( USB1 REQUIRED )

include_directories( "./src" 
                     ${LIBUSB_INCLUDE_DIR} 
                   )

find( GLOB src "./src/*.cpp" )
set( libs ${LIBUSB_LIBRARIES} )

add_library( ${proj} STATIC ${src} )
target_link_libraries( ${proj} ${libs} )







