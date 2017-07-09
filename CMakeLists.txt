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

##FIND GLEW##
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARY_DIRS})
add_definitions(${GLEW_DEFINITIONS})
if(NOT GLEW_FOUND)
    message(ERROR " GLEW not found!")
endif(NOT GLEW_FOUND)

##FIND GLFW##
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

include_directories(${CMAKE_DL_LIBS})
include_directories(${OPENDCP_LIB})

file(GLOB SOURCES "Source/*.cpp" "Source/*.c")
add_executable(Particles main.cpp ${SOURCES})

target_link_libraries(Particles ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} ${GLEW_STATIC_LIBRARIES} ${CMAKE_DL_LIBS} ${CMAKE_DL_LIBS})
