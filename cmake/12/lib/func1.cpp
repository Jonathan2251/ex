#include <fstream>
#include <iostream>

using namespace std;

void func() {
  cout << "func1.cpp::func()" << endl;
}

int func1() {
  func();
  return 3;
}
