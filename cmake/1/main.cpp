#include <iostream>

extern int func1();
extern int func2();

using namespace std;

int main() {
  cout << "total is = " << func1() << " characters" << endl;
  cout << "file content is : " << endl;
  func2();
  return 0;
}
