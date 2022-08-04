// ~/llvm/release/build/bin/clang dsl.cpp

#include <cstdio>

enum Precision {
  Bit32,
  Bit16
};

// our NNLib
class Matrix {
protected:
  Precision prec;
  int x, y;
public:
  Matrix(int X, int Y, Precision Prec) {
    x = X;
    y = Y;
    prec = Prec;
  }
  Matrix operator*(Matrix const &B) {
    static Matrix res(x, y, prec);
    // ...
    return res;
  }
  /*
  Matrix operator=(Matrix const &B) {
    assert(this->prec == B->prec);
    ...
  }*/
};

const Precision bit16 = Bit16;

class Mat64: public Matrix {
public:
  Mat64() : Matrix(64, 64, bit16) {};
  Mat64& operator*(Mat64 const &B) {
    static Mat64 C;
    //asm("matmul this->data, B.data");
    C = *this;
    //C += B;
    return C;
  }
};

int t[32] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
};

template <class T>
class Vec32 {
public:
  T *data;
  Vec32(T *array) {};
  Vec32& operator*(const int scalar) {
    static Vec32<T> res(t);
	// inline asm vadd scalar, this->data
    return res;
  } 
  Vec32& operator+(Vec32 const &B) {
    static Vec32<T> res(t);
    //printf("vadd this->data, B.data");
    // inline asm for riscv vadd
    return res;
  }
};

int gA[128] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
};

int main() {
  Vec32<int> A(gA), B(gA+32), C(gA+64);
  A = B + C;
  return 0;
}
