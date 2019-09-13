#include <stdio.h>

int main() {
  int x = 2 * fgetc(stdin) - 180;
  int y = 5 / x; // Divide by zero
  return 0;
}
