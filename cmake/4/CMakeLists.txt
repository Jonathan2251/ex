# Demonstration for how to set execution file, lib and copy input file to build folder in cmake

# $ rm -rf build; mkdir build; cd build
# $ cmake -DCMAKE_BUILD_TYPE=Debug -DTARGETS_TO_BUILD=(|CPU1|CPU2|ALL) .. // for instance -DTARGETS_TO_BUILD= : none of lib_cpu1 or lib_cpu2 is linked
# $ make VERBOSE=1 
# $ ./water

cmake_minimum_required(VERSION 3.10)
project(water)

add_executable(water main.cpp)

# List of all targets to be built by default:
set(ALL_TARGETS
    CPU1
    CPU2
)

foreach(t ${ALL_TARGETS})
    set (${t} 0)
endforeach(t)

if (NOT TARGETS_TO_BUILD)
  # if no TARGETS_TO_BUILD in cmake command
  set(TARGETS_TO_BUILD "")
endif()

if (TARGETS_TO_BUILD STREQUAL "")
elseif (TARGETS_TO_BUILD STREQUAL "CPU1")
  add_subdirectory("lib_cpu1")
  target_link_libraries(water cpu1)
elseif (TARGETS_TO_BUILD STREQUAL "CPU2")
  add_subdirectory("lib_cpu2")
  target_link_libraries(water cpu2)
elseif (TARGETS_TO_BUILD STREQUAL "ALL")
  add_subdirectory("lib_cpu1")
  add_subdirectory("lib_cpu2")
  target_link_libraries(water cpu1 cpu2)
  set (TARGETS_TO_BUILD ${ALL_TARGETS})
else()
  message(FATAL_ERROR
    "TARGETS_TO_BUILD must in (|CPU1|CPU2|ALL)")
endif()

message("TARGETS_TO_BUILD: " ${TARGETS_TO_BUILD})
foreach(t ${TARGETS_TO_BUILD})
  set(${t} 1)
endforeach(t)

foreach(t ${ALL_TARGETS})
  if (${t} STREQUAL 1)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D${t}")
  endif()
endforeach(t)
message("CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})


file(COPY foobar.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# removes any cached value and rely on either the default or the provided one
# ref. https://stackoverflow.com/questions/53159371/how-to-create-a-cmake-variable-that-takes-a-default-value-unless-explicitly-over
unset(TARGETS_TO_BUILD CACHE)
