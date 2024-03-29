// pass: ~/riscv/riscv_newlib/bin/clang++ vadd.c  -menable-experimental-extensions -march=rv64gcv0p10 -O0 -mllvm --riscv-v-vector-bits-min=256 -S -v
// ~/riscv/riscv_newlib/bin/clang++ vadd.c -march=rv64g -O0 -S -emit-llvm : fail as below
// /local/riscv/riscv_newlib/lib/clang/13.0.1/include/riscv_vector.h:18:2: error: "Vector intrinsics require the vector extension."

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <riscv_vector.h>

#include "common.h"

#define VADD_ASM

// Vector-vector add
void vadd(uint32_t *a, const uint32_t *b, const uint32_t *c, size_t n) {
  while (n > 0) {
    size_t vl = vsetvl_e32m8(n);
    vuint32m8_t vb = vle32_v_u32m8(b, vl);
// generate:
//   vsetvli zero, a0, e32, m8, ta, mu
//   vadd.vv v8, v8, v16
    vuint32m8_t vc = vle32_v_u32m8(c, vl);
    vuint32m8_t va = vadd(vb, vc, vl);
    vse32(a, va, vl);
    a += vl;
    b += vl;
    c += vl;
    n -= vl;
  }
}

void vadd_mask(uint32_t *a, const uint32_t *b, const uint32_t *c, uint8_t *m, size_t n) {
  while (n > 0) {
    size_t vl = vsetvl_e32m8(n);
    // Mask type = LMUL/SEW
    vbool4_t mask = vle1_v_b4(m, vl);
    vuint32m8_t vb = vle32_v_u32m8(b, vl);
    vuint32m8_t vc = vle32_v_u32m8(c, vl);
    vuint32m8_t va = vadd(mask, vundefined_u32m8(), vb, vc, vl);
    vse32(a, va, vl);
    vse1_v_b4(m, mask, vl);
    a += vl;
    b += vl;
    c += vl;
    n -= vl;
  }
}

#ifdef VADD_ASM
// Vector-vector add (inline assembly)
void vadd_asm(uint32_t *a, const uint32_t *b, const uint32_t *c, size_t n) {
  while (n > 0) {
    size_t vl;
    vuint32m8_t va, vb, vc;
#if 0
    // origin
    __asm__ __volatile__ ( "vsetvli %[vl], %[n], e32, m8" : [vl] "=r"(vl) : [n] "r"(n) );
// Fail:
// vadd.c:58:28: error: operand must be e[8|16|32|64|128|256|512|1024],m[1|2|4|8|f2|f4|f8],[ta|tu],[ma|mu]
//    __asm__ __volatile__ ( "vsetvli %[vl], %[n], e32, m8" : [vl] "=r"(vl) : [n] "r"(n) );
//                           ^
// <inline asm>:1:18: note: instantiated into assembly here
//         vsetvli a0, a0, e32, m8
//                         ^
#else
    //__asm__ __volatile__ ( "vsetvli %[vl], %[512], e32, m8" : [vl] "=r"(vl) : [512] "r"(512) );
// Fail: same as above
#endif
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
#endif

uint32_t a[4096];
uint8_t m[512];

int main(void) {
  enable_mstatus_vs();

  // init source
  //for (size_t i = 0; i < array_size(a); ++i)
  for (size_t i = 0; i < 4096; ++i)
    a[i] = i;

  //vadd(a, a, a, array_size(a));
  vadd(a, a, a, 4096);

  //for (size_t i = 0; i < array_size(a); ++i)
  for (size_t i = 0; i < 4096; ++i)
    assert(a[i] == i * 2);
  printf("The results of vadd:\tPASS\n");

  // init mask array, set all elements active
  //for (size_t i = 0; i < array_size(m); ++i)
  for (size_t i = 0; i < 512; ++i)
    m[i] = 255;

  //vadd_mask(a, a, a, m, array_size(a));
  vadd_mask(a, a, a, m, 4096);

  //for (size_t i = 0; i < array_size(a); ++i)
  for (size_t i = 0; i < 4096; ++i)
    assert(a[i] == i * 4);

#ifdef VADD_ASM
  //vadd_asm(a, a, a, array_size(a));
  vadd_asm(a, a, a, 4096);
#endif

  //for (size_t i = 0; i < array_size(a); ++i)
  for (size_t i = 0; i < 4096; ++i)
    assert(a[i] == i * 8);
  printf("The results of vadd_asm:\tPASS\n");

  return 0;
}

