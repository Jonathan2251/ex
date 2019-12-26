# Demonstration for how to set CMAKE_CXX_FLAGS in different folder

# $ rm -rf build; mkdir build; cd build
# $ cmake -DCMAKE_BUILD_TYPE=Debug .. // check display: CMAKE_CXX_FLAGS:  -O0 -DDEBUG -std=c++14 -Werror -Wuninitialized  CMAKE_CXX_FLAGS in lib folder:  -O0 -DDEBUG -std=c++14 -Werror=return-type -Wuninitialized
# build$ make VERBOSE=1 // func1.cpp is warning since -Werror=return-type, main.cpp is error since -Werror

cmake_minimum_required(VERSION 3.10)
project(water)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -DDEBUG -std=c++14 -Werror -Wuninitialized")
else ()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++14 -Werror -Wuninitialized")
endif ()
message("CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})

file(COPY foobar.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(water main.cpp)
target_link_libraries(water wa)

add_subdirectory("lib")
