#include "cstdio"
#include "string.h"

struct Info {
  char name[100];
};

struct InfoA : public Info {
  size_t id;
};

struct Node {
  Info* info;
  Node(Info *aInfo) {
    info = aInfo;
  }
};

InfoA* getInfoA(Node* n) {
  //static Info* info = n->info;
  Info* info = n->info;
  return static_cast<InfoA*>(info);
}

int main() {
  InfoA infoA;
  strcpy(infoA.name, "A");
  infoA.id = 1;
  Node node(&infoA);
  InfoA p = *getInfoA(&node);
  printf("p.name:%s, p.id:%lu\n", p.name, p.id);
}
