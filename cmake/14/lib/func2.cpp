#include <fstream>
#include <iostream>

using namespace std;

void func() {
  cout << "func2.cpp::func()" << endl;
}

void func2() {
  func();
}
