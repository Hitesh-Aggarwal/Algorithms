#include <stdio.h>
#include <stdlib.h>

#define N 10

int max(int a, int b) { return (a > b) ? a : b; }

int memoized_cut_rod_aux(int *p, int n, int *r) {
  if (r[n] >= 0) return r[n];
  int q;
  if (n == 0)
    q = 0;
  else {
    q = -1;
    for (int i = 0; i < n; i++)
      q = max(q, p[i] + memoized_cut_rod_aux(p, n - i - 1, r));
  }
  r[n] = q;
  return q;
}

int memoized_cut_rod(int *p, int n) {
  int r[N + 1];
  for (int i = 0; i < N + 1; i++)
    r[i] = -1;
  return memoized_cut_rod_aux(p, n, r);
}

int extended_memoized_cut_rod_aux(int *p, int n, int *r, int *s) {
  if (r[n] >= 0) return r[n];
  int q;
  int a;
  if (n == 0)
    q = 0;
  else {
    q = -1;
    for (int i = 1; i <= n; i++) {
      a = extended_memoized_cut_rod_aux(p, n - i, r, s);
      if (q < p[i - 1] + a) {
        q = p[i - 1] + a;
        s[n] = i;
      }
    }
  }
  return q;
}

void print_extended_memoized_cut_rod(int *p, int n) {
  int r[N + 1], s[N + 1];
  for (int i = 0; i <= n; i++) {
    r[i] = -1;
    r[i] = -1;
  }
  extended_memoized_cut_rod_aux(p, n, r, s);
  while (n > 0) {
    printf("%d ", s[n]);
    n = n - s[n];
  }
  printf("\n");
}

int bottom_up_cut_rod(int *p, int n) {
  int r[N + 1];
  r[0] = 0;
  for (int i = 1; i <= n; i++) {
    int q = -1;
    for (int j = 1; j <= i; j++)
      q = max(q, p[j - 1] + r[i - j]);
    r[i] = q;
  }
  return r[n];
}

void extended_bottom_up_cut_rod(int *p, int n, int *r, int *s) {
  r[0] = 0;
  for (int i = 1; i <= n; i++) {
    int q = -1;
    for (int j = 1; j <= i; j++)
      if (q < p[j - 1] + r[i - j]) {
        q = p[j - 1] + r[i - j];
        s[i] = j;
      }
    r[i] = q;
  }
}

void print_cut_rod_solution(int *p, int n) {
  int r[N + 1], s[N + 1];
  extended_bottom_up_cut_rod(p, n, r, s);
  while (n > 0) {
    printf("%d ", s[n]);
    n = n - s[n];
  }
  printf("\n");
}

int cut_rod(int *p, int n) {
  if (n == 0) return 0;
  int q = -1;
  for (int i = 0; i < n; i++)
    q = max(q, p[i] + cut_rod(p, n - i - 1));
  return q;
}

int main(int argc, char *argv[]) {
  int p[N] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
  printf("%d\n", bottom_up_cut_rod(p, N));
  print_cut_rod_solution(p, N);
  return 0;
}
