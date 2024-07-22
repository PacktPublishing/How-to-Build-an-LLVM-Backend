// Shift left 322512 by `input` bits.
// If input is > 31 we want to clamp to 31.
// If input is < 0 we want to shift right instead of left (and still clamp to
// 31.)
// As it is this function has undefined behavior.
int fctWithUB(int input) {
  return 322512 >> input;
}
