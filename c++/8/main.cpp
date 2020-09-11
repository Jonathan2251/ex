// g++ -O0 -static-libasan -g -fsanitize=address main.cpp
#include <string>

using namespace std;

struct AA {
  int id;
  string name;
};

AA *copy1(AA *x) {
  AA* a = new AA();
  a->id = x->id;
  a->name = x->name;
  return a;
}

int main() {
  AA x;
  x.id = 1;
  x.name = "x";
  AA* y;
  y = copy1(&x);
//  delete(y);
}
