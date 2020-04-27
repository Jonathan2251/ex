# CMAKE_CURRENT_SOURCE_DIR can be skipped
file(GLOB LIB_SRC1 ${CMAKE_CURRENT_SOURCE_DIR}/func1.cpp
)

file(GLOB LIB_SRC2 ${CMAKE_CURRENT_SOURCE_DIR}/func2.cpp
)

add_library(wa1 SHARED ${LIB_SRC1})
add_library(wa2 SHARED ${LIB_SRC2})
