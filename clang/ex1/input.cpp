#include "input.h"

// _Noreturn is just an example for adding your keyword before your DSL function.
// OpenCL uses __kernel to highlight devices' entry function.
_Noreturn void test(double x, double &res) {
  double result = A::
               abs(x);
  res = result;
}
