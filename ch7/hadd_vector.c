typedef struct {
  int a, b, c, d;
} Vec4;

int hadd(const Vec4 *input) {
  return input->a + input->b + input->c + input->d;
}
