// ~/llvm/release/build/bin/clang -target riscv64-unknown-linux-gnu -S ch8_1_1.cpp -emit-llvm -o ch8_1_1.ll
// ~/llvm/release/build/bin/llc --version   // display register targets
// ~/llvm/release/build/bin/llc -march=riscv64 -mcpu=help   // display registered cpus
// ~/llvm/release/build/bin/llc -march=riscv64 -mcpu=generic-rv64 -relocation-model=static -filetype=asm ch8_1_1.ll -o -
// ~/llvm/release/build/bin/llc -march=riscv64 -mcpu=generic-rv64 -relocation-model=pic -filetype=asm ch8_1_1.ll -o -

/// start
int test_ifctrl()
{
  unsigned int a = 0;
  
  if (a == 0) {
    a++; // a = 1
  }
  
  return a;
}
