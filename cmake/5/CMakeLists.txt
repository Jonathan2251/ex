# Demonstration for how to set execution file, lib and copy input file to build folder in cmake

# $ rm -rf build; mkdir build; cd build
# $ cmake -DCMAKE_BUILD_TYPE=Debug -DTARGETS_TO_BUILD=(|cpu1|cpu2|all) .. // for instance -DTARGETS_TO_BUILD= : none of lib_cpu1 or lib_cpu2 is linked
# $ make VERBOSE=1 
# $ ./water

cmake_minimum_required(VERSION 3.10)
project(water)

add_executable(water main.cpp)

# List of all targets to be built by default:
set(ALL_TARGETS
    cpu1
    cpu2
)

foreach(t ${ALL_TARGETS})
  set (${t} 0)
endforeach(t)

# function ref. https://stackoverflow.com/questions/14375519/how-to-write-a-nice-function-that-passes-variables-by-reference
# PARENT_SCOPE: This command will set the value of a variable into the parent directory or calling function (whichever is applicable to the case at hand)
# PARENT_SCOPE: https://cmake.org/cmake/help/latest/command/set.html#set-normal-variable
function(get_targets arg targets)
  if (${arg} STREQUAL "")
    message("arg empty")
    set (${targets} "" PARENT_SCOPE)
  elseif (${arg} STREQUAL "cpu1")
    message("arg STREQUAL \"cpu1\"")
    set (${targets} "cpu1" PARENT_SCOPE)
  elseif (${arg} STREQUAL "cpu2")
    set (${targets} "cpu2" PARENT_SCOPE)
  elseif (${arg} STREQUAL "all")
    set (${targets} ${ALL_TARGETS} PARENT_SCOPE)
  else()
    message(FATAL_ERROR "TARGETS_TO_BUILD must in (|cpu1|cpu2|all)")
  endif()
endfunction(get_targets)

if (NOT TARGETS_TO_BUILD)
  # if no TARGETS_TO_BUILD in cmake command
  set(TARGETS_TO_BUILD "")
  message("NOT TARGETS_TO_BUILD")
endif()


message("TARGETS_TO_BUILD: " ${TARGETS_TO_BUILD})
get_targets(TARGETS_TO_BUILD TARGETS)
message("TARGETS: " ${TARGETS})

foreach(t ${TARGETS})
  add_subdirectory("lib_${t}")
  target_link_libraries(water ${t})
  set(${t} 1)
endforeach(t)

foreach(t ${TARGETS})
  if (${t} STREQUAL 1)
    string(TOUPPER ${t} T)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D${T}")
  endif()
endforeach(t)
message("CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})


file(COPY foobar.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# removes any cached value and rely on either the default or the provided one
# ref. https://stackoverflow.com/questions/53159371/how-to-create-a-cmake-variable-that-takes-a-default-value-unless-explicitly-over
unset(TARGETS_TO_BUILD CACHE)
