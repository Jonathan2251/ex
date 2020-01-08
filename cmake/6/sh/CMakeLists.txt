# when ${CMAKE_CURRENT_BINARY_DIR}/hello.sh is removed, it trigger "cp ${CMAKE_CURRENT_SOURCE_DIR}/hello.sh ${CMAKE_CURRENT_BINARY_DIR}/hello.sh" before call "bash ${CMAKE_CURRENT_BINARY_DIR}/hello.sh"
function(bind command from_shell to_shell)
  add_custom_command(OUTPUT ${to_shell}
    COMMAND cp ${from_shell} ${to_shell}
    DEPENDS ${from_shell}
    COMMENT "cp ${from_shell} ${to_shell}"
  )
  add_custom_target(${command}
    COMMAND bash ${to_shell}
    DEPENDS ${to_shell}
    VERBATIM
  )
endfunction(bind)

file(COPY hello.sh DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY world.sh DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

bind(hello ${CMAKE_CURRENT_SOURCE_DIR}/hello.sh ${CMAKE_CURRENT_BINARY_DIR}/hello.sh)
bind(world ${CMAKE_CURRENT_SOURCE_DIR}/world.sh ${CMAKE_CURRENT_BINARY_DIR}/world.sh)
