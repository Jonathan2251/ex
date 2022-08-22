Work on llvm e8a397203c67adbeae04763ce25c6a5ae76af52c of 12.x

build:
  bash dsp-cpp-to-cpp.sh
run:
  ./build/DslCppToCpp input.cpp
check:
  cat output.cpp
