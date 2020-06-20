
#include <iostream>

namespace N1 {
class DataNode {
public:
  int x;
  int y;
};
} // namespace


class A {
public:
  int id;
};

namespace N1 {
class B {
public:
  N1::DataNode dn;
  A a;
};

} // namespace

using namespace std;

int main() {
  N1::B b;

  return 0;
}
