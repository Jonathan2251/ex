#include <fstream>

int func1() {
  std::ifstream is("foobar.txt");     // open file

  int i = 0;
  char str[1024];
  while (is.getline(str, 1024)) {        // loop getting single characters
    i++;
  }

  is.close();
  int x;
  x += 1;
  return i;
}
