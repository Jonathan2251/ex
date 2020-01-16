# string and list
# cmake ..

# https://stackoverflow.com/questions/13582282/cmake-difference-between-and

cmake_minimum_required(VERSION 3.10)

# In CMake, a "list" is a string of items separated by semi-colons
# https://stackoverflow.com/questions/16433391/cmake-list-append-for-compiler-flags-yields-bogus-results
set(X "one" "two" "three")
set(Y "")
set(Z "foo")

set(A "${X} ${Y} ${Z}")
set(A1 "\"${X} ${Y} ${Z}\"")
set(B ${X} ${Y} ${Z})
set(C "${X}" "${Y}" "${Z}")

message("\$\{A\}: ${A}")
list(LENGTH A numA)
message("\$\{numA\}: ${numA}")

message("\$\{A1\}: ${A1}")
list(LENGTH A1 numA1)
message("\$\{numA1\}: ${numA1}")

message("\$\{B\}: ${B}")
list(LENGTH B numB)
message("\$\{numB\}: ${numB}")

message("\$\{C\}: ${C}")
list(LENGTH C numC)
message("\$\{numC\}: ${numC}")
