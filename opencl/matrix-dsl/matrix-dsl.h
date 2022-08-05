
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

template <class T>
class Mat4 {
private:
  Precision prec;
  T *data[4];
public:
  Mat4(T *A);
  void Init();
  Mat4& operator*(const Mat4 &B);
  void Print();
};

template <class T>
class Vec32 {
private:
  Precision prec;
public:
  T *data;
  Vec32(T *A);
  Vec32& Mul(const T Scalar);
  Vec32& operator*(const T Scalar);
  Vec32& operator+(const Vec32 &B);
  void Print();
};

template <class T>
Vec32<T>& operator*(const T Scalar, Vec32<T> &B);
