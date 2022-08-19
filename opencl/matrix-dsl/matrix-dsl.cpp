/* ~/riscv/riscv_newlib/bin/clang++ matrix-dsl.cpp -menable-experimental-extensions \
-march=rv64gcv0p10 -O0 -mllvm --riscv-v-vector-bits-min=256 -v */
// ~/riscv/git/qemu/build/qemu-riscv64 -cpu rv64,v=true a.out
// ~/riscv/riscv_newlib/bin/riscv64-unknown-elf-objdump -d a.out|grep vmul

#include "matrix-dsl.h"
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <riscv_vector.h>

#define USE_RVV

const Precision bit16 = Bit16;

uint32_t t[32] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
};

template <class T>
Mat4<T>::Mat4(T *A) {
  data[0] = A;
  data[1] = A+4;
  data[2] = A+8;
  data[3] = A+12;
}

template <class T>
void Mat4<T>::Init() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      data[i][j] = 0;
    }
  }
}

template <class T>
Mat4<T>& Mat4<T>::operator*(const Mat4 &B) {
  static Mat4 res(t);
  res.Init();
  //asm("matmul this->data, B.data");
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      int value = 0;
      for (int k = 0; k < 4; k++) {
        value += data[i][k]*B.data[k][j];
      }
      res.data[i][j] = value;
    }
  }
  return res;
}

template <class T>
void Mat4<T>::Print() {
  for (int i=0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      printf("%d ", data[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

template <class T>
Vec32<T>::Vec32(T *A) {
  data = A;
}

template <class T>
Vec32<T>& Vec32<T>::Mul(const T Scalar) {
  static Vec32<T> res(t);
#ifdef USE_RVV
  size_t vl = vsetvl_e32m8(32);
  vuint32m8_t vb = vle32_v_u32m8(data, vl);
  vuint32m8_t va = vmul(vb, Scalar, vl);
  vse32(res.data, va, vl);
#else
  for (int i=0; i < 32; i++) {
    res.data[i] = Scalar*data[i];
  }
#endif
  return res;
}

template <class T>
Vec32<T>& Vec32<T>::operator*(const T Scalar) {
  return Mul(Scalar);
} 

template <class T>
Vec32<T>& Vec32<T>::operator+(const Vec32 &arg) {
  static Vec32<T> res(t);
#ifdef USE_RVV
  size_t vl = vsetvl_e32m8(32);
  vuint32m8_t vb = vle32_v_u32m8(data, vl);
  vuint32m8_t vc = vle32_v_u32m8(arg.data, vl);
  vuint32m8_t va = vadd(vb, vc, vl);
  vse32(res.data, va, vl);
#else
  for (int i=0; i < 32; i++) {
    res.data[i] = data[i]+arg.data[i];
  }
#endif
  return res;
}

template <class T>
void Vec32<T>::Print() {
  for (int i=0; i < 32; i++) {
    printf("%d ", data[i]);
  }
  printf("\n");
}

template <class T>
Vec32<T>& operator*(const T Scalar, Vec32<T> &B) {
  return B * Scalar;
}

uint32_t gV[32*3] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
};

uint32_t gM[16*4] = {
  0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3,
  0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3,
  0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3,
};

int main() {
  Vec32<uint32_t> A(gV), B(gV+32), C(gV+64);
  uint32_t alpha = (uint32_t)2;
  A = alpha*B + C;
  printf("B: "); B.Print();
  printf("C: "); C.Print();
  printf("A: "); A.Print();
  printf("\n\n");

  // multiply and add, madd
  // A = B * C + D; 
  // Solve above by class is not efficient, class does not use madd.
  // DSL: extend clang to parsing the left and calling A = madd(B,C,D); can get better performance.

  Mat4<uint32_t> M1(gM), M2(gM+16), M3(gM+32);
  M1 = M2 * M3; 
  printf("M1: \n"); M1.Print();
  printf("M2: \n"); M2.Print();
  printf("M3: \n"); M3.Print();

  return 0;
}
