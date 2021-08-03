#include <cstddef>

void f1(int);
void f2(int *);
void f3(char *);
void f4(int, int *);

template <typename T> void fn(T *);

void test(void) {
  f1(0);
  f2(0);       // Non-compliant
  f3(0);       // Non-compliant
  f3(nullptr);
  f4(0, 0);    // Non-compliant

  int *x = 0;      // Non-compliant
  bool y = x == 0; // Non-compliant
  int *a = nullptr;
  bool b = a == nullptr;

  fn<int>(0); // Non-compliant
}
