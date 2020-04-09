#include <iostream>

extern int func1();
extern int func2();

using namespace std;

int main() {
  func1();
  func2();
  return 0;
}
