#include <stdio.h>

int buildIntLittleEndian(const char *input) {
  int res = 0;
  for (int i = 0; i < sizeof(res); ++i) {
    res |= input[i] << (8 * i);
  }
  return res;
}

int buildIntBigEndian(const char *input) {
  int res = 0;
  for (int i = 0; i < sizeof(res); ++i) {
    res <<= 8;
    res |= input[i];
  }
  return res;
}

int main() {
  char input[] = {0x01, 0x02, 0x03, 0x04};
  int val = buildIntLittleEndian(input);
  int valBig = buildIntBigEndian(input);
  printf("little: 0x%08x\nbig:    0x%08x\n", val, valBig);
  return 0;
}
