#include <fstream>
#include <iostream>

void func2() {
  std::ifstream is("foobar.txt");     // open file

  char c;
  while (is.get(c)) {        // loop getting single characters
    std::cout << c;
  }

  is.close();
}
