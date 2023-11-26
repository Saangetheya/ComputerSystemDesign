int f(int a)
{
  int k;
  return a;
}
int main()
{
  int k, r;
  k = 1;
  for (k = 1; k < 2; k++)
  {
    int lal;
    lal = 2;
    r++;
  }
  int lal;
  lal = 3;
  function<int(int, int)> fi = [&](int a, int b)
  {
    int c[10];
    c[7] = a + b + lal;

    return c[7];
  };
  int j;
  j = 1;

  fi(0, 1);
  return 0;
}
