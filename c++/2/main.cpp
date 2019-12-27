// g++ options:
// -Wno-unused-but-set-variable: set uninitialized int variables to 0
// -Wuninitialized: enable warning for uninitialized variables
// -Werror treat warining to error

// g++ -O0 -g -Wno-unused-but-set-variable main.cpp 
// g++ -O0 -g main.cpp

// https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html

#include <iostream>

using namespace std;

int foo() {
  int x;

  x += 1;
  cout << x << endl;
}

int main() {
  int a = foo();

  return 0;
}
