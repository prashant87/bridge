
cmake_minimum_required(VERSION 3.1)
project( "emg_gui" )

set( CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/_app )
set( ROOT ${CMAKE_CURRENT_SOURCE_DIR} )


set( IBASE ${OGRE_HOME}/include/OGRE )
set( LBASE ${OGRE_HOME}/lib )

set( OGRE_LIBS ${LBASE}/libOgreMain.so 
               ${LBASE}/libOgreBites.so 
               ${LBASE}/libOgreOverlay.so 
               ${LBASE}/libOgrePaging.so 
               ${LBASE}/libOgreProperty.so 
               ${LBASE}/libOgreRTShaderSystem.so 
               ${LBASE}/libOgreTerrain.so )

set( OGRE_INCLUDES
  ${OGRE_INCLUDE_DIRS}
  ${IBASE}
  ${IBASE}/Bites 
  ${IBASE}/RTShaderSystem 
  ${IBASE}/Overlay
   )

add_subdirectory( "./3dparty" )
#add_subdirectory( "./app" )
add_subdirectory( "./io" )



