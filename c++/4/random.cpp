/* rand example: guess the number */
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <fstream>

using namespace std;

int main ()
{
  unsigned char val;
  ofstream OutFile("input.bin", ios::out | ios::binary);
  /* initialize random seed: */
  srand (time(NULL));

  printf("RAND_MAX = %d\n", RAND_MAX);
  printf("sizeof(char) = %lu\n", sizeof(char));
  for (size_t i = 0; i < 1; i++) {
    for (size_t j = 0; j < 4; j++) {
      for (size_t k = 0; k < 224; k++) {
        for (size_t l = 0; l < 224; l++) {
          /* generate secret number between 1 and 10: */
          int iVal = rand();
          // printf("%d ", iVal);
          val = (iVal % 256);
          printf("%d ", val);
          OutFile.write( (char*)&val, sizeof(unsigned char));
        }
        printf("\n");
      }
    }
  }
  OutFile.close();
}
