#include <stdio.h>
#include <stdlib.h>
#define N 10

void count_sort(int *arr, int n, int k) {
  int *C = (int *)malloc(sizeof(int) * (k + 1));
  int *B = (int *)malloc(sizeof(int) * n);
  for (int i = 0; i <= k; i++)
    C[i] = 0;
  for (int i = 0; i < n; i++)
    C[arr[i]] = C[arr[i]] + 1;
  for (int i = 1; i <= k; i++)
    C[i] = C[i] + C[i - 1];
  for (int i = n - 1; i >= 0; i--) {
    B[C[arr[i]] - 1] = arr[i];
    C[arr[i]]--;
  }
  for (int i = 0; i < n; i++)
    arr[i] = B[i];

  free(C);
  free(B);
}

int main(int argc, char *argv[]) {
  int A[N] = {3, 10, 7, 9, 8, 2, 5, 6, 4, 1};
  count_sort(A, N, 10);
  for (int i = 0; i < N; i++)
    printf("%d ", A[i]);
  printf("\n");

  return 0;
}
