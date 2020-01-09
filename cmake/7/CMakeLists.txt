# function and variables
# cmake ..
# cmake -DANIMIALS=bird ..

cmake_minimum_required(VERSION 3.10)

# ${ARGV} holds the list of all arguments given to the macro and ${ARGN} holds the list of arguments past the last expected argument
function(stringappend varName)
  message("\$\{varName\}: ${varName}")
  message("\$\{\$\{varName\}\}: ${${varName}}")
  message("\$\{ARGV\}: ${ARGV}")
  message("\$\{ARGN\}: ${ARGN}")

  # after the following set varName is a list
  set(${varName} "${${varName}}" "${ARGN}" PARENT_SCOPE)
endfunction()

if (NOT ANIMIALS)
  set (ANIMIALS "")
endif()
message("\$\{ANIMIALS\}: ${ANIMIALS}")
stringappend(ANIMIALS "cat" "dog")
message("\$\{ANIMIALS\}: ${ANIMIALS}")
list(LENGTH ANIMIALS num_animials)
message("\$\{num_animials\}: ${num_animials}")

# https://cmake.org/cmake/help/latest/command/string.html#replace
# "${ANIMIALS}", not ${ANIMIALS}
string (REPLACE ";" " " ANIMIALS2 "${ANIMIALS}")
message("\$\{ANIMIALS2\}: ${ANIMIALS2}")

# removes any cached value and rely on either the default or the provided one
# ref. https://stackoverflow.com/questions/53159371/how-to-create-a-cmake-variable-that-takes-a-default-value-unless-explicitly-over
unset(ANIMIALS CACHE)
