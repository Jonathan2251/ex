# Demonstration for how to call bash command in cmake

# rm -rf build; mkdir build; cd build
# cmake ..  // no foobar.txt
# make zoo  // generate foobar.txt
# rm foobar.txt; make zoo // generate foobar.txt again

# References:
# https://gist.github.com/baiwfg2/39881ba703e9c74e95366ed422641609

cmake_minimum_required(VERSION 3.10)
project(water)

# command cat not run on CMAKE_CURRENT_SOURCE_DIR, so need it on the following
set(IN_FILES ${CMAKE_CURRENT_SOURCE_DIR}/foo.txt ${CMAKE_CURRENT_SOURCE_DIR}/bar.txt)
set(OUT_FILE "foobar.txt")

# add_custom_command does not create a new target. You have to define targets explicitly
# by add_executable, add_library or add_custom_target in order to make them visible to make
add_custom_command(OUTPUT ${OUT_FILE}
    COMMAND cat ${IN_FILES} > ${OUT_FILE}
    DEPENDS ${IN_FILES}
    # Display the given message before the commands are executed at build time
    COMMENT "Creating ${OUT_FILE}"
)

# target zoo is always built
add_custom_target(zoo ALL
    COMMAND echo "This is ALL target 'zoo', and it depends on ${OUT_FILE}"
    # If the file exists, then commands related to that file won't be executed
    # DONOT let other target depends on the same OUTPUT as current target,
    #   or it may be bad when doing parallel make
    DEPENDS ${OUT_FILE}

    # to make quotes printable,for example
    VERBATIM
)

# CMAKE_CURRENT_SOURCE_DIR can be skipped
file(GLOB LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/func1.cpp
                  func2.cpp
)

add_library(wa ${LIB_SRC})
add_dependencies(wa zoo)

add_executable(water main.cpp)
target_link_libraries(water wa)
