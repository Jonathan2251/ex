#include <iostream>

#ifdef CPU1
extern int func1();
#endif

#ifdef CPU2
extern int func2();
#endif

using namespace std;

int main() {
#ifdef CPU1
  cout << "total is = " << func1() << " lines" << endl;
#endif
#ifdef CPU2
  cout << "file content is : " << endl;
  func2();
#endif
  return 0;
}
