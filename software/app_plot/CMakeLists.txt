
set( proj gui )

find_package( OpenAL  REQUIRED )
find_package( Threads REQUIRED )
find_package( Boost COMPONENTS serialization REQUIRED )

set( libs ${OPENAL_LIBRARIES}
          ${CMAKE_THREAD_LIBS_INIT}
          )

# the search paths
include_directories( "./src"
                     "./pa"
                     ${OGRE_INCLUDE_DIRS}
                     ${OGRE_INCLUDE_DIR} 
                     ${OGRE_INCLUDE_DIR}/Bites 
                     ${OGRE_INCLUDE_DIR}/Overlay 
                     ${OGRE_INCLUDE_DIR}/RTShaderSystem
                     ${OPENAL_INCLUDE_DIRS}
                     ${ROOT}/io/src
                     ${ROOT}/3dparty/gpr/include/gaussian_process_regression
                     ${ROOT}/3dparty/eigen3
                    )
link_directories(${OGRE_LIBRARY_DIRS})

set( IMGUI ${ROOT}/3dparty/ogreimgui )

set(IMGUI_SRCS ${IMGUI}/imgui/imgui.cpp ${IMGUI}/imgui/imgui_draw.cpp)
set(OGRE_IMGUI_SRCS ${IMGUI}/ImguiManager.cpp ${IMGUI}/ImguiRenderable.cpp)
if(FREETYPE_FOUND)
  include_directories(${IMGUI}/imgui/misc/freetype/)
  list(APPEND IMGUI_SRCS ${IMGUI}/imgui/misc/freetype/imgui_freetype.cpp)
endif()

include_directories(${IMGUI} ${IMGUI}/imgui/ ./src)

if(FREETYPE_FOUND)
    target_compile_definitions(OgreImgui PRIVATE -DUSE_FREETYPE)
    target_include_directories(OgreImgui PRIVATE ${FREETYPE_INCLUDE_DIRS})
endif()

file( GLOB src "./src/*.cpp" )

add_executable( ${proj} ${src} ${IMGUI}/imgui/imgui_demo.cpp )
target_compile_features( ${proj} PRIVATE cxx_range_for )
target_link_libraries( ${proj} OgreImgui io pthread ${libs} ${Boost_LIBRARIES} )

if(NOT FREETYPE_FOUND)
    set(FREETYPE_FOUND "FALSE")
endif()
message(STATUS "using freetype: ${FREETYPE_FOUND}")

install( TARGETS ${proj} DESTINATION ./ )
install( DIRECTORY "./media/" DESTINATION ./my )





