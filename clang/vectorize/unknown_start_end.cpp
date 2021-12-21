// ~/llvm/release/build/bin/clang++ -O3 -emit-llvm -S unknown_start_end.cpp -o unknown_start_end.vectorize.ll -fvectorize
// ~/llvm/release/build/bin/clang++ -O3 -emit-llvm -S unknown_start_end.cpp -o unknown_start_end.no-vectorize.ll -fno-vectorize

void bar(float *A, float* B, float K, int start, int end) {
  for (int i = start; i < end; ++i)
    A[i] *= B[i] + K;
}
