#include "../include/Verifier.h"

int main() {
  int x = input();
  assume(x > 1);
  assert(x > 0);
  return x;
}
