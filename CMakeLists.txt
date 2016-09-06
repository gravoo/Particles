cmake_minimum_required (VERSION 2.8)
##Project name
project (Particles)
set(CMAKE_CXX_FLAGS "-std=c++14 -g -Wall")
# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
include_directories("${PROJECT_SOURCE_DIR}" Include)

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

file(GLOB SOURCES "Source/*.cpp")
add_executable(Particles main.cpp ${SOURCES})

target_link_libraries(Particles ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
