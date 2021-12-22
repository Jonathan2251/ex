// /local/riscv_newlib/bin/clang slp.cpp -S -o slp.slp-vectorize.s
// /local/riscv_newlib/bin/clang slp.cpp -S -fno-slp-vectorize -o slp.no-slp-vectorize.s

void foo(int a1, int a2, int b1, int b2, int *A) {
  A[0] = a1*(a1 + b1);
  A[1] = a2*(a2 + b2);
  A[2] = a1*(a1 + b1);
  A[3] = a2*(a2 + b2);
}
