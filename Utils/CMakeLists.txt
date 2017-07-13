cmake_minimum_required (VERSION 2.8)

##Project name
project (Utils)
set(CMAKE_CXX_FLAGS "-std=c++17 -g -Wall")

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

#Bring the headers, such as Student.h into the project
include_directories(Include)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "Source/*.cpp")

#Generate the shared library from the sources
add_library(testStudent SHARED ${SOURCES})

#Set the location for library installation -- i.e., /usr/lib in this case
# not really necessary in this example. Use "sudo make install" to apply
install(TARGETS testStudent DESTINATION ${CMAKE_BINARY_DIR})
