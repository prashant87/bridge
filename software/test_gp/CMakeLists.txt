
set( proj "test_gp" )

file( GLOB src "./src/*.cpp" )

include_directories( "./src" 
                     ${ROOT}/3dparty/gpr/include/gaussian_process_regression
                     ${ROOT}/3dparty/eigen3 )

add_executable( ${proj} ${src} )
target_compile_features( ${proj} PRIVATE cxx_range_for )


