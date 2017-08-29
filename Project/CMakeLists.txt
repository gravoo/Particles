cmake_minimum_required (VERSION 3.5)
##Project name
project (Particles)
add_compile_options(-Wall -Wextra -Wpedantic)
set(CMAKE_CXX_FLAGS "-std=c++17 ")

#Include files for project
include_directories(${PROJECT_SOURCE_DIR} Include)
include_directories(${PROJECT_SOURCE_DIR} glad/include)
include_directories(${PROJECT_SOURCE_DIR} Utils/Include)
include_directories(${PROJECT_SOURCE_DIR} glm)

#For the shared own library:
set(PROJECT_LINK_LIBS libUtils.a)
link_directories(${PROJECT_SOURCE_DIR}/Utils/build)

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
add_executable(Particles ${SOURCES} glad/src/glad.c)

target_link_libraries(Particles ${PROJECT_LINK_LIBS} ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} ${GLEW_STATIC_LIBRARIES} ${CMAKE_DL_LIBS} ${CMAKE_DL_LIBS})
