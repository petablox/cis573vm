#include <stdio.h>

int main() {
  int i, a = 0, b = fgetc(stdin);
  for (i = 10000; i > 0; i--)
    printf("%d\n", b * b / (i - b));
  return 0;
}
