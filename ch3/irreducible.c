extern void someFct();

int irreducible(int shouldSkip1stCall) {
  int i = 0;
  if (shouldSkip1stCall)
    goto SKIP;
  do {
    someFct();
    SKIP:;
  } while (++i < 7);
  return 32;
}
