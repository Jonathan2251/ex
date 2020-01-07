function(bind command shell)
  file(COPY ${shell} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${shell}
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/${shell} ${shell}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${shell}
    COMMENT "cp ${CMAKE_CURRENT_SOURCE_DIR}/${shell} ${CMAKE_CURRENT_BINARY_DIR}/${shell}"
  )
  add_custom_target(${command}
    COMMAND bash ${shell}
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${shell}
    VERBATIM
  )
endfunction(bind)

bind(hello hello.sh)
bind(world world.sh)
