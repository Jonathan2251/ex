
file(COPY foobar.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(water main.cpp)
target_link_libraries(water wa1)
target_link_libraries(water wa2)

add_executable(water2 main2.cpp)
target_link_libraries(water2 wa1)
target_link_libraries(water2 wa2)
