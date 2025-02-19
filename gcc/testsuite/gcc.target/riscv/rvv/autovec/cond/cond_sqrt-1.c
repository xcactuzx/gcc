/* { dg-do compile } */
/* { dg-additional-options "-march=rv64gcv_zvfh -mabi=lp64d --param riscv-autovec-preference=scalable -fno-vect-cost-model -ffast-math" } */

#include <stdint.h>

#define DEF_LOOP(TYPE, OP)                                                     \
  void __attribute__ ((noipa))                                                 \
  test_##TYPE##_##OP (TYPE *__restrict r, TYPE *__restrict a,                  \
		      TYPE *__restrict pred, int n)                            \
  {                                                                            \
    for (int i = 0; i < n; ++i)                                                \
      r[i] = pred[i] ? OP (a[i]) : a[i];                                       \
  }

#define TEST_ALL(T)                                                            \
  T (_Float16, __builtin_sqrtf16)                                              \
  T (float, __builtin_sqrtf)                                                   \
  T (double, __builtin_sqrt)

TEST_ALL (DEF_LOOP)

/* { dg-final { scan-assembler-times {\tvfsqrt\.v\tv[0-9]+,v[0-9]+,v0\.t} 3 } } */

/* { dg-final { scan-assembler {\tvsetvli\t[a-z0-9]+,[a-z0-9]+,e[0-9]+,m[f0-9]+,t[au],mu} } } */
