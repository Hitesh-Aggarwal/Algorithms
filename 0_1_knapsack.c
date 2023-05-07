#include <stdio.h>
#include <stdlib.h>

#define N 3

void fill_knapsack(int v[], int w[], int n, int *C, int W) { /* C is n x W matrix */
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < W; j++) {
      if (w[i] <= j) {
        if (v[i] + C[i * W + j - w[i]] > C[i * W + j])
          C[(i + 1) * W + j] = v[i] + C[i * W + j - w[i]];
        else
          C[(i + 1) * W + j] = C[i * W + j];
      } else
        C[(i + 1) * W + j] = C[i * W + j];
    }
  }
}

void print_solution(int *values, int *weights, int n, int W) {
  int C[n + 1][W + 1];
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= W; j++)
      C[i][j] = 0;
  }
  fill_knapsack(values, weights, N + 1, (int *)C, W + 1);
  int i = N, k = W;
  while (i > 0 && k > 0) {
    if (C[i][k] != C[i - 1][k]) {
      printf("%d ", i);

      i = i - 1;
      k = k - weights[i];
    } else
      i = i - 1;
  }
  printf("\nTotal Cost: %d", C[n][W]);
}

int main(int argc, char *argv[]) {
  int values[N] = {60, 100, 120};
  int weights[N] = {10, 20, 30};
  int W = 50;
  print_solution(values, weights, N + 1, W + 1);
  printf("\n");
  return EXIT_SUCCESS;
}
