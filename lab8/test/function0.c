int f(int *x) { return *x + 1; }
char g(char x) { return x; }
void h() {}

int main() {
  int a = 1;
  int b = f(&a);
  char c = g(1);
  int d = b + 1;
  char e = c + 1;
  h();
  return 0;
}
