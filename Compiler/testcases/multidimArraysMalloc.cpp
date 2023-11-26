int main()
{
  int n, m, i;
  n = 20;
  m = 30;
  int **A;
  A = malloc(sizeof(*) * n);
  for (i = 0; i < n; i++)
  {
    A[i] = malloc(sizeof(int) * m);
  }
  int j;
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < m; j++)
    {
      A[i][j] = 1;
    }
  }

  return 0;
}