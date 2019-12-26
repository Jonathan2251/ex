# CMAKE_CURRENT_SOURCE_DIR can be skipped
file(GLOB LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/func1.cpp
                  func2.cpp
)

add_library(wa ${LIB_SRC})
