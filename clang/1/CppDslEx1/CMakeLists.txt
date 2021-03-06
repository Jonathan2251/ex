add_llvm_library(CppDslEx1 MODULE
    MyASTConsumer.cpp
    MyFrontendAction.cpp
  PLUGIN_TOOL clang)

if(LLVM_ENABLE_PLUGINS AND (WIN32 OR CYGWIN))
  set(LLVM_LINK_COMPONENTS
    Support
  )
  clang_target_link_libraries(CppDslEx1 PRIVATE
    clangAST
    clangBasic
    clangFrontend
    )
endif()
