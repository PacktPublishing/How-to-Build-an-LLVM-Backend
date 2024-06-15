void foo(short * restrict dst, short * restrict A, short * restrict B ) {
  for (long long i = 0; i != 24; ++i)
    dst[i] = A[i] + B[i];
}
