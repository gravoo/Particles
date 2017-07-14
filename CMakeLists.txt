cmake_minimum_required (VERSION 2.8)
##Project name
project (Particles)
set(CMAKE_CXX_FLAGS "-std=c++17 -g -Wall")

#Include files for project
include_directories(${PROJECT_SOURCE_DIR} Include)
include_directories(${PROJECT_SOURCE_DIR} glad/include)

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

file(GLOB SOURCES "Source/*.cpp")
add_executable(Particles main.cpp ${SOURCES} glad/src/glad.c)

target_link_libraries(Particles ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} ${GLEW_STATIC_LIBRARIES} ${CMAKE_DL_LIBS} ${CMAKE_DL_LIBS})
