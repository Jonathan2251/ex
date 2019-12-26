#include <iostream>

extern int func1();
extern int func2();

using namespace std;

int main() {
  cout << "total is = " << func1() << " lines" << endl;
  cout << "file content is : " << endl;
  func2();

  int x;
  x += 1;

  return 0;
}
