// ~/llvm/release/build/bin/clang++ -O3 -emit-llvm -S known_start_end.cpp -o known_start_end.vectorize.ll -fvectorize
// ~/llvm/release/build/bin/clang++ -O3 -emit-llvm -S known_start_end.cpp -o known_start_end.no-vectorize.ll -fno-vectorize
#define LOOP_SIZE 50

void bar(float *A, float* B, float K) {
  for (int i = 0; i < LOOP_SIZE; ++i)
    A[i] *= B[i] + K;
}
