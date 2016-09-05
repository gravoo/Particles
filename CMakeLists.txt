cmake_minimum_required (VERSION 2.8)
##Project name
project (PARTICLES)
set(CMAKE_CXX_FLAGS "-std=c++14 -g -Wall")

##FIND OPENGL##
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
        message(ERROR " OPENGL not found!")
    endif(NOT OPENGL_FOUND)
##FIND GLUT##
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
        message(ERROR " GLUT not found!")
    endif(NOT GLUT_FOUND)
add_executable(Particles main.cpp)
target_link_libraries(Particles ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
