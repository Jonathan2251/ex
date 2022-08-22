Work on llvm e8a397203c67adbeae04763ce25c6a5ae76af52c of 12.x

build:
  bash build_vs_released_binary.sh
run:
  ./build/CppDslEx2 input.cpp
check:
  cat output.cpp
