cmake_minimum_required(VERSION 2.6)

project(3D-engine)

file(
  GLOB_RECURSE
  sources
  src/*.cpp
)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
#include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} )


include_directories(include/glew include/freeglut)
include_directories(include/3D-engine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

add_executable(
  3D-engine
  ${sources}
)

target_link_libraries(3D-engine ${OPENGL_LIBRARY} ${GLEW_LIBRARY} ${GLUT_LIBRARY} )
