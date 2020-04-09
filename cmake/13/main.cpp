#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cstring>

using namespace std;

int main(int argc, char** argv) {
  if (argc != 2) {
    cout << "./water {cpu1|cpu2}: for example: ./water 1" << endl;
    return 0;
  }
  assert(strcmp(argv[1], "cpu1") == 0 || strcmp(argv[1], "cpu2") == 0);
  if (strcmp(argv[1], "cpu1") == 0) {
     system("./water1");
  }
  else if (strcmp(argv[1], "cpu2") == 0) {
     system("./water2");
  }
  return 0;
}
