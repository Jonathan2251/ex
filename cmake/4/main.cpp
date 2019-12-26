#include <iostream>

#ifdef CPU1
extern int func1();
#endif

#ifdef CPU2
extern int func2();
#endif

#ifdef CPU1
#define CPU_BIT0 1
#endif

#ifdef CPU2
#define CPU_BIT1 1
#endif

#define TARGET (CPU_BIT0||(CPU_BIT1 < 1))

using namespace std;

int main() {
#ifdef CPU1
  cout << "total is = " << func1() << " lines" << endl;
#endif
#ifdef CPU2
  cout << "file content is : " << endl;
  func2();
#endif
#if TARGET == (CPU1|CPU2)
  cout << "TARGET == (CPU1|CPU2)" << endl;
#endif
  return 0;
}
