

set( proj "test_app" )

include_directories( "./src"
                     ${ROOT}/io/src )

file( GLOB src "./src/*.cpp" )

add_executable( ${proj} ${src} )
target_link_libraries( ${proj} io )
target_compile_features( ${proj} PRIVATE cxx_range_for )
install( TARGETS ${proj} DESTINATION "./" )


