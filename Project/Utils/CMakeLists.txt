cmake_minimum_required (VERSION 2.8)

##Project name
project (Utils)
set(CMAKE_CXX_FLAGS "-std=c++17 -g -Wall")

#Bring the headers, such as Student.h into the project
include_directories(Include)
include_directories(${PROJECT_SOURCE_DIR} ../glad/include)
set(CMAKE_BUILD_TYPE Release)

##FIND GLFW##
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "Source/*.cpp")

#Generate the shared library from the sources
add_library(Utils STATIC ${SOURCES})

#Set the location for library installation -- i.e., /usr/lib in this case
# not really necessary in this example. Use "sudo make install" to apply
install(TARGETS Utils DESTINATION ${CMAKE_BINARY_DIR})
