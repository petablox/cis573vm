#include <stdio.h>

int main() {
  int u1 = fgetc(stdin);
  int u2 = 4, d;
  if (u1 != 0) {
    d = u2 / u1; // Divide by zero
  } else {
    int d = u2 / (u1 + 1); // Divide by zero
  }
  return 0;
}
