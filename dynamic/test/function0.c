int f(int i) {
  return i;
}

int main(int argc, char **argv) {
  int a;
  if(argc > 2)
    a = 1;
  else
    a = -1;

  int r = f(a);

  return 0;
}
