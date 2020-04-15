/* rand example: guess the number */
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <fstream>

using namespace std;

int main ()
{
  float val;
  ofstream OutFile("input_bin", ios::out | ios::binary);
  /* initialize random seed: */
  srand (time(NULL));

  printf("RAND_MAX = %d\n", RAND_MAX);
  for (size_t i = 0; i < 1; i++) {
    for (size_t i = 0; i < 3; i++) {
      for (size_t i = 0; i < 224; i++) {
        for (size_t i = 0; i < 224; i++) {
          /* generate secret number between 1 and 10: */
          int iVal = rand();
          // printf("%d ", iVal);
          val = ((float)iVal / (float)RAND_MAX);
          printf("%.16f", val);
          OutFile.write( (char*)&val, sizeof(float));
        }
        printf("\n");
      }
    }
  }
  OutFile.close();
}
