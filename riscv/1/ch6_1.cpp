// ~/llvm/13/llvm-project/build/bin/clang -target riscv64-unknown-linux-gnu -S ch6_1.cpp -emit-llvm -o ch6_1.ll
// ~/llvm/13/llvm-project/build/bin/clang -target riscv64-unknown-linux-gnu -c -mno-relax ch6_1.cpp -o ch6_1.o
// ~/llvm/13/llvm-project/build/bin/llc -march=riscv64 -mcpu=generic-rv64 -relocation-model=static -filetype=asm ch6_1.ll -o -
// ~/llvm/13/llvm-project/build/bin/llc -march=riscv64 -mcpu=generic-rv64 -relocation-model=static -filetype=obj ch6_1.ll -o ch6_1.o
// ~/llvm/13/llvm-project/build/bin/llvm-readelf -r ch6_1.o
// ~/llvm/13/llvm-project/build/bin/lld -flavor gnu ch6_1.o -o a.out
// ~/llvm/13/llvm-project/build/bin/llvm-objdump -d a.out

/// start
int gStart = 3;
int gI = 100;
int test_global()
{
  int c = 0;

  c = gI;

  return c;
}

int main()
{
  bool pass = true;
  pass = test_global();
  return pass;
}
