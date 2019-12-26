# For what I tried, CMAKE_CXX_FLAGS apply to the whole folder. set_source_files_properties(func1.cpp PROPERTIES COMPILE_FLAGS -Werror=return-type) to apply one specific file is not work

string(REPLACE -Werror -Werror=return-type CXX_FLAGS ${CMAKE_CXX_FLAGS})
set(CMAKE_CXX_FLAGS ${CXX_FLAGS})
message("CMAKE_CXX_FLAGS in lib folder: " ${CMAKE_CXX_FLAGS})

# CMAKE_CURRENT_SOURCE_DIR can be skipped
file(GLOB LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/func1.cpp
                  func2.cpp
)

add_library(wa ${LIB_SRC})
