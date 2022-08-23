Work on llvm e8a397203c67adbeae04763ce25c6a5ae76af52c of 12.x

build:
  bash build_vs_released_binary.sh
run:
  ./build/CppDslEx2 input.cpp
check:
  cat output.cpp
gdb:
  ~/git/ex/clang/2$ gdb --args ./build/CppDslEx2 input.cpp 
  (gdb) b MyASTConsumer.cpp:61
  (gdb) r
  61	    TheRewriter.ReplaceText(CallerSR, StringRef(sBuiltinFunc));
