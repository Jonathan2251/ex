#include <fstream>

int func1() {
  std::ifstream is("foobar.txt");     // open file

  int i = 0;
  char c;
  while (is.get(c)) {        // loop getting single characters
    i++;
  }

  is.close();
  return i;
}
