#include <iostream>

using namespace std;

#define CPU1 1
#define CPU2 2
#define CPU3 4

#define ARCH (CPU1|CPU2)
//#define ARCH CPU2

int main() {
  #if (ARCH & CPU1) == CPU1
    cout << "(ARCH & CPU1) CPU1\n";
  #endif
  #if (ARCH & CPU2) == CPU2
    cout << "(ARCH & CPU2) CPU2\n";
  #endif
  #if (ARCH & CPU3) == CPU3
    cout << "(ARCH & CPU3) CPU3\n";
  #endif
  cout << "ARCH = " << ARCH << endl;
  return 0;
}
