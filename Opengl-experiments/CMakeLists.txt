cmake_minimum_required (VERSION 3.8)

project ("Opengl-experiments")


#Conan
set(CONAN_DISABLE_CHECK_COMPILER "true")
include("conan_cmake/conanbuildinfo.cmake")
conan_basic_setup()


#CXX

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Sources
set(HEADERS "scene.hpp")
set(SOURCES "main.cpp")

add_executable (Opengl-experiments ${HEADERS} ${SOURCES} )

#Link conan libs
target_link_libraries(Opengl-experiments ${CONAN_LIBS})
