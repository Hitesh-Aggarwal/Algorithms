#include <stdio.h>
#include <stdlib.h>

#define N 10

int max(int a, int b) { return (a > b) ? a : b; }

int cut_rod(int *p, int n) {
  if (n == 0)
    return 0;
  int q = -1;
  for (int i = 0; i < n; i++)
    q = max(q, p[i] + cut_rod(p, n - i - 1));
  return q;
}

int main(int argc, char *argv[]) {
  int p[N] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
  printf("%d\n", cut_rod(p, 4));

  return 0;
}
