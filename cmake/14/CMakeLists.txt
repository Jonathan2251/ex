# Demonstration for how to set execution file, lib and copy input file to build folder in cmake

# $ rm -rf build; mkdir build; cd build
# $ cmake -DCMAKE_BUILD_TYPE=Debug .. // check display: CMAKE_CXX_FLAGS:  -O0 -DDEBUG
# build$ ls foobar.txt 
# foobar.txt 
# $ make VERBOSE=1 // -O0 -DDEBUG -g: has -g 
# $ ./water

cmake_minimum_required(VERSION 3.10)
project(water)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -DDEBUG")
else ()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif ()
message("CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})

add_subdirectory("lib")
add_subdirectory("bin")
