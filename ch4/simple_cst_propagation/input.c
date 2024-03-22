int foo(int tst) {
  int a = 3 + 2;
  a <<= 3;
  if (tst)
    a /= 5;
  else
    a |= 0xF0F;
  return a;
}

int bar(int tst) {
  unsigned a = 0xFFFFFFFF;
  a <<= 3;
  if (tst)
    a /= 3;
  else
    a |= 0xF0F;
  ++a;
  return (int)a;
}

