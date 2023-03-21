#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define N 6

int matrix_chain_multiply_brute_force(int *p, int i, int j) {
  if (i == j)
    return 0;
  else {
    int min = INT_MAX;
    for (int k = i; k < j; k++) {
      int left = matrix_chain_multiply_brute_force(p, i, k);
      int right = matrix_chain_multiply_brute_force(p, k + 1, j);
      int cost = p[i - 1] * p[k] * p[j];
      if (min > (left + right + cost)) min = left + right + cost;
    }
    return min;
  }
}

// m and s are 2D arrays of dimensions nxn
void matrix_chain_order(int *p, int *m, int n) {
  for (int i = 0; i < n; i++)
    m[i * n + i] = 0;
  for (int l = 2; l <= n; l++) {
    for (int i = 1; i <= n - l + 1; i++) {
      int j = i + l - 1;
      m[(i - 1) * n + (j - 1)] = INT_MAX;
      for (int k = i; k < j; k++) {
        int q = m[(i - 1) * n + (k - 1)] + m[k * n + (j - 1)] + p[i - 1] * p[k] * p[j];
        if (q < m[(i - 1) * n + (j - 1)]) {
          m[(i - 1) * n + (j - 1)] = q;
          m[(j - 1) * n + (i - 1)] = k;
        }
      }
    }
  }
}

void print_optimal_parens(int *s, int i, int j, int n) {
  if (i == j) {
    char *sub[] = {"\xe2\x82\x80",
                   "\xe2\x82\x81",
                   "\xe2\x82\x82",
                   "\xe2\x82\x83",
                   "\xe2\x82\x84",
                   "\xe2\x82\x85",
                   "\xe2\x82\x86",
                   "\xe2\x82\x87",
                   "\xe2\x82\x88",
                   "\xe2\x82\x89"};
    if (i < 10)
      printf("A%s", sub[i]);
    else
      printf("A[%d]", i);

  } else {
    printf("(");
    print_optimal_parens(s, i, s[(j - 1) * n + i - 1], n);
    print_optimal_parens(s, s[(j - 1) * n + i - 1] + 1, j, n);
    printf(")");
  }
}

int main(int argc, char *argv[]) {
  int p[N + 1] = {30, 35, 15, 5, 10, 20, 25};
  int m[N][N];
  matrix_chain_order(p, (int *)m, N);
  // printf("%d\n", matrix_chain_multiply_brute_force(p, 1, 20));
  print_optimal_parens((int *)m, 1, N, N);
  printf("\nTotal Cost: %d\n", m[0][N - 1]);
  return 0;
}
