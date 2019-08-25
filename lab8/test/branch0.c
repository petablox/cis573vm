int main() {
  int x = 1;
  int y = 2;
  int z = x + y;
  char *p;
  char a = 'a';
  char b = 'b';
  if (z > 0) {
    p = &a;
  } else {
    p = &b;
  }
  return 0;
}
