#ifndef COMMON_H
#define COMMON_H

#define static_assert_exp(exp, msg) ((void) sizeof(struct { _Static_assert(exp, msg); int dummy; }))
#define array_size(a) (static_assert_exp(!__builtin_types_compatible_p(__typeof__(a), __typeof__(&(a)[0])), "array_size called on non-array expression"), sizeof(a) / sizeof((a)[0]))

static inline void enable_mstatus_vs(void) {
  __asm__ __volatile__ ( "csrs mstatus, %0" :: "r"((unsigned long) 1 << 9) );
}

#endif
