#include <cstdio>

// our NNLib
class Matrix {
protect:
  precision prec;
  int
public:
  Matrix operator*(Matrix const &B) {
    Matrix res;
    ...
    return res;
  }
  /*
  Matrix operator=(Matrix const &B) {
    assert(this->prec == B->prec);
    ...
  }*/
}

class Mat64: public Matrix {
public:
  Mat64() : Matrix(64, 64, 16-bit);
  Mat64 operator*(Mat64 const &B) {
    static Mat64 C;
    asm("matmul this->data, B.data");
    C = *this;
    C += B;
  }
}

class Vec32 {
public:
  Vec32() {};
  Vec32 operator+(Vec32 const &B) {
    printf("vadd this->data, B.data");
  }
};

int main() {
  Vec32 A, B, C;
  A = B + C;
  return 0;
}
