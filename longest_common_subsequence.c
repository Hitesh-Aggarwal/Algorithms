#include <stdio.h>
#include <stdlib.h>

#define M 7
#define N 6

int max(int a, int b) { return (a > b) ? a : b; }

int lcs_brute_force(char *X, char *Y, int m, int n) {
  if (m == -1 || n == -1)
    return 0;
  else {
    if (X[m] == Y[n])
      return (1 + lcs_brute_force(X, Y, m - 1, n - 1));
    else
      return max(lcs_brute_force(X, Y, m - 1, n), lcs_brute_force(X, Y, m, n - 1));
  }
}

int lcs_memoized_aux(char *X, char *Y, int m, int n, int *C) {
  if (m == -1 || n == -1)
    return 0;
  else if (C[m * N + n] > -1) {
    return C[m * N + n];
  } else {
    int val = 0;
    if (X[m] == Y[n])
      val = 1 + lcs_memoized_aux(X, Y, m - 1, n - 1, C);
    else
      val = max(lcs_memoized_aux(X, Y, m - 1, n, C), lcs_memoized_aux(X, Y, m, n - 1, C));

    C[m * N + n] = val;
    return val;
  }
}

int lcs_memoized(char *X, char *Y, int m, int n) {
  int C[M][N];
  for (int i = 0; i < M; i++)
    for (int j = 0; j < N; j++)
      C[i][j] = -1;
  return lcs_memoized_aux(X, Y, m, n, (int *)C);
}

void lcs_length(char *X, char *Y, int m, int n, int *b, int *c) {
  for (int i = 1; i <= m; i++)
    c[i * (N + 1) + 0] = 0;
  for (int j = 0; j <= n; j++)
    c[0 * (N + 1) + j] = 0;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (X[i - 1] == Y[j - 1]) {
        c[i * (N + 1) + j] = c[(i - 1) * (N + 1) + j - 1] + 1;
        b[i * (N + 1) + j] = 2;
      } else if (c[(i - 1) * (N + 1) + j] >= c[i * (N + 1) + j - 1]) {
        c[i * (N + 1) + j] = c[(i - 1) * (N + 1) + j];
        b[i * (N + 1) + j] = 1;
      } else {
        c[i * (N + 1) + j] = c[i * (N + 1) + j - 1];
        b[i * (N + 1) + j] = 0;
      }
    }
  }
}

void print_lcs(char *X, char *Y, int m, int n) {
  int c[M + 1][N + 1];
  int b[M + 1][N + 1];
  lcs_length(X, Y, m, n, (int *)b, (int *)c);
  int i = m, j = n;
  int arr[M];
  int k = 0;
  while (i >= 1 && j >= 1) {
    if (b[i][j] == 2) {
      arr[k++] = X[i - 1];
      i = i - 1;
      j = j - 1;
    } else if (b[i][j] == 1)
      i = i - 1;
    else
      j = j - 1;
  }
  while (k > 0) {
    printf("%c", arr[k - 1]);
    k--;
  }
  printf("\n");
}

void print_lcs_aux(int *b, char *X, int i, int j) {
  if (i == 0 || j == 0) return;
  if (b[i * (N + 1) + j] == 2) {
    print_lcs_aux(b, X, i - 1, j - 1);
    printf("%c", X[i - 1]);
  } else if (b[i * (N + 1) + j] == 1)
    print_lcs_aux(b, X, i - 1, j);
  else
    print_lcs_aux(b, X, i, j - 1);
}

void print_lcs_recursive(char *X, char *Y, int m, int n) {
  int c[M + 1][N + 1];
  int b[M + 1][N + 1];
  lcs_length(X, Y, m, n, (int *)b, (int *)c);
  print_lcs_aux((int *)b, X, m, n);
  printf("\n");
}

int main(int argc, char *argv[]) {
  char X[M] = "abcbdab";
  char Y[N] = "bdcaba";

  print_lcs(X, Y, M, N);
  print_lcs_recursive(X, Y, M, N);
  return 0;
}
