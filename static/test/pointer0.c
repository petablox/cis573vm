int f(){
  int a;
  int *c = &a;
  int *d = &a;
  *c = 0;
  int x = 1 / *d;
  return 0;
}
