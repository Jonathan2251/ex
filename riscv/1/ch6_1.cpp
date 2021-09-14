// ~/llvm/release/build/bin/clang -target riscv64-unknown-linux-gnu -S ch6_1.cpp -emit-llvm -o ch6_1.ll
// ~/llvm/release/build/bin/llc -march=riscv64 -mcpu=generic-rv64 -relocation-model=static -filetype=asm ch6_1.ll -o -
// ~/llvm/release/build/bin/llc -march=riscv64 -mcpu=generic-rv64 -relocation-model=static -filetype=obj ch6_1.ll -o ch6_1.o
// ~/llvm/release/build/bin/llvm-readelf -tr ch6_1.o
// ~/llvm/release/build/bin/lld -flavor gnu ch6_1.o -o a.out
// ~/llvm/release/build/bin/llvm-objdump -d a.out

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
