#include "cstdio"
#include "string.h"

// default member value

class Info {
private:
  const char* name = nullptr;
public:
  Info() {
  }
  Info(const char* Name) {
    name = Name;
  }
  const char* Name() {
    return name;
  }
};

const char animal[100] = "duck";

int main() {
  Info infoA;
  printf("infoA.Name():%s\n", infoA.Name());
  Info infoB(animal);
  printf("infoB.Name():%s\n", infoB.Name());
  Info infoC("bird");
  printf("infoC.Name():%s\n", infoC.Name());
}
