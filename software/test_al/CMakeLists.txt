
set( proj "test_al" )

find_package( OpenAL REQUIRED )

include_directories( "./src"
                     ${OPENAL_INCLUDE_DIRS} 
                   )
file( GLOB src "./src/*.cpp" )

link_libraries( ${OPENAL_LIBRARIES} )
add_executable( ${proj} ${src} )
target_compile_features( ${proj} PRIVATE cxx_range_for )


