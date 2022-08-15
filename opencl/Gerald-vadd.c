
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <riscv_vector.h>
#include <math.h>
#include "common.h"
typedef float float32_t;
// Vector-vector add (inline assembly)
void vadd_asm(uint32_t *a, const uint32_t *b, const uint32_t *c, size_t n) {
  while (n > 0) {
    size_t vl;
    vuint32m8_t va, vb, vc;
    __asm__ __volatile__ ( "vsetvli %[vl], %[n], e32, m8" : [vl] "=r"(vl) : [n] "r"(n) );
#if (__clang_major__ > 10)
    __asm__ __volatile__ ( "vle32.v %[vb], (%[b])" : [vb] "=vr"(vb) : [b] "r"(b) : "memory" );
    __asm__ __volatile__ ( "vle32.v %[vc], (%[c])" : [vc] "=vr"(vc) : [c] "r"(c) : "memory" );
    __asm__ __volatile__ ( "vadd.vv %[va], %[vb], %[vc]" : [va] "=vr"(va) : [vb] "vr"(vb), [vc] "vr"(vc) );
    __asm__ __volatile__ ( "vse32.v %[va], (%[a])" : [va] "=vr"(va) : [a] "r"(a) : "memory" );
#else
    __asm__ __volatile__ ( "vle32.v %[vb], (%[b])" : [vb] "=v8"(vb) : [b] "r"(b) : "memory" );
    __asm__ __volatile__ ( "vle32.v %[vc], (%[c])" : [vc] "=v8"(vc) : [c] "r"(c) : "memory" );
    __asm__ __volatile__ ( "vadd.vv %[va], %[vb], %[vc]" : [va] "=v8"(va) : [vb] "v8"(vb), [vc] "v8"(vc) );
    __asm__ __volatile__ ( "vse32.v %[va], (%[a])" : [va] "=v8"(va) : [a] "r"(a) : "memory" );
#endif
    a += vl;
    b += vl;
    c += vl;
    n -= vl;
  }
}
uint32_t a[4096];
uint8_t m[512];
float32_t vrb[4096*4];
float32_t vra[4];
uint16_t vib[4096*4];
uint16_t via[4];

int main(void) {
  enable_mstatus_vs();
#if 0
  // init source
  for (size_t i = 0; i < array_size(a); ++i)
    a[i] = i;
  //for (size_t i = 0; i < array_size(vrb); ++i)
  for (size_t i = 0; i < 4096*4; ++i)
    vrb[i] = i+1;
  for (size_t i = 0; i < array_size(vib); ++i)
    vib[i] = i;

  for (size_t i = 0; i < array_size(a); ++i)
    assert(a[i] == i * 2);
  printf("The results of vadd:\tPASS\n");
  // init mask array, set all elements active
  for (size_t i = 0; i < array_size(m); ++i)
    m[i] = 255;
  for (size_t i = 0; i < array_size(a); ++i)
    assert(a[i] == i * 4);
#endif
  //vadd_asm(a, a, a, array_size(a));
  vadd_asm(a, a, a, 4096*4);
  //for (size_t i = 0; i < array_size(a); ++i)
  for (size_t i = 0; i < 4096*4; ++i)
    assert(a[i] == i * 8);
  printf("The results of vadd_asm:\tPASS\n");
  return 0;
}


