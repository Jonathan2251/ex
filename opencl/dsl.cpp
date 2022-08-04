// ~/llvm/release/build/bin/clang dsl.cpp

#include <cstdio>

enum Precision {
  Bit32,
  Bit16
};

#if 0
template <class T>
class Matrix {
protected:
  Precision prec;
  int x, y;
  T *data;
public:
  Matrix(int X, int Y, Precision Prec) {
    x = X;
    y = Y;
    prec = Prec;
  }
  Matrix operator*(const Matrix &B) {
    assert(prec == B.prec);
    assert(x == B.x);
    assert(y == B.y);
    static Matrix res(x, y, prec);
    for (int i = 0; i < x; i++) {
      for (int j = 0; j < y; j++) {
        res.data[i][j] += data[i][j]*B.data[j][i];
      }
    return res;
  }
  /*
  Matrix operator=(Matrix const &B) {
    assert(this->prec == B->prec);
    ...
  }*/
};
#endif

// our NNLib
const Precision bit16 = Bit16;

int t[32] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
};

template <class T>
class Mat4 {
private:
  Precision prec;
  T *data[4];
public:
  Mat4(T *A) {
    data[0] = A;
    data[1] = A+4;
    data[2] = A+8;
    data[3] = A+12;
  }
  void Init() {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        data[i][j] = 0;
      }
    }
  }
  Mat4& operator*(const Mat4 &B) {
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
  void print() {
    for (int i=0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        printf("%d ", data[i][j]);
      }
      printf("\n");
    }
    printf("\n");
  }
};

template <class T>
class Vec32 {
private:
  Precision prec;
  T *data;
public:
  Vec32(T *A) {
    data = A;
  }
  Vec32& operator*(const T scalar) {
    static Vec32<T> res(t);
	// inline asm vadd scalar, this->data
    for (int i=0; i < 32; i++) {
      res.data[i] = scalar*data[i];
    }
    return res;
  } 
  Vec32& operator+(const Vec32 &B) {
    static Vec32<T> res(t);
    //printf("vadd this->data, B.data");
    // inline asm for riscv vadd
    for (int i=0; i < 32; i++) {
      res.data[i] = data[i]+B.data[i];
    }
    return res;
  }
  void print() {
    for (int i=0; i < 32; i++) {
      printf("%d ", data[i]);
    }
    printf("\n");
  }
};

int gV[32*3] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
};

int gM[16*4] = {
  0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3,
  0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3,
  0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3,
};

int main() {
  Vec32<int> A(gV), B(gV+32), C(gV+64);
  A = B + C;
  printf("B: "); B.print();
  printf("C: "); C.print();
  printf("A: "); A.print();
  A = A*2;
  printf("A: "); A.print();
  printf("\n\n");

  Mat4<int> M1(gM), M2(gM+16), M3(gM+32);
  M1 = M2 * M3; 
  printf("M1: \n"); M1.print();
  printf("M2: \n"); M2.print();
  printf("M3: \n"); M3.print();

  return 0;
}
