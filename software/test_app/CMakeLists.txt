

set( proj "test_app" )

include_directories( "./src" )

file( GLOB src "./src/*.cpp" )

add_executable( ${proj} ${src} )
target_link_libraries( ${proj} io )
install( TARGETS ${proj} DESTINATION "./" )


