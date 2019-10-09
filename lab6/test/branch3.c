#include <stdio.h>

void f() {
  int x = fgetc(stdin);
  int y = 0;
  if (x > 10) {
    y = 1;
  } else {
    y = 2;
  }
  int z = x / y; 
}
