long long foo(long long *in, long long ub) {
  for (long long i = 0; i < ub; ++i)
    if (in[i] != 0)
      return i;
  return -1;
}
