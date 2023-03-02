#include <stdio.h>
#include <stdlib.h>

#define N 5
float w[N + 2][N + 1];
float e[N + 2][N + 1];
int root[N + 1][N + 1];

void optimal_bst(float *p, float *q) {
  int j;
  float t;
  for (int i = 1; i <= N + 1; i++) {
    e[i][i - 1] = q[i - 1];
    w[i][i - 1] = q[i - 1];
  }

  for (int l = 1; l <= N; l++) {
    for (int i = 1; i <= N - l + 1; i++) {
      j = i + l - 1;
      e[i][j] = 10000;
      w[i][j] = w[i][j - 1] + p[j] + q[j];
      for (int r = i; r <= j; r++) {
        t = e[i][r - 1] + e[r + 1][j] + w[i][j];
        if (t < e[i][j]) {
          e[i][j] = t;
          root[i][j] = r;
        }
      }
    }
  }
}

int main(int argc, char *argv[]) {
  float p[N + 1] = {0, 0.15, 0.10, 0.05, 0.10, 0.20};
  float q[N + 1] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
  optimal_bst(p, q);
  for (int i = 0; i <= N + 1; i++) {
    for (int j = 0; j <= N; j++)
      printf("%.2f ", e[i][j]);
    printf("\n");
  }
  printf("\n\n");
  for (int i = 0; i <= N + 1; i++) {
    for (int j = 0; j <= N; j++)
      printf("%.2f ", w[i][j]);
    printf("\n");
  }
  printf("\n\n");
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++)
      printf("%d ", root[i][j]);
    printf("\n");
  }
  return 0;
}
