/* Compile with gcc radix_sort.c -o radix_sort -lm */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define N 13

void count_sort(int *arr, int n, int k, int d) {
  // sort on the ith digit.
  /*
     ones digit:
     (arr[j] % 10) / 1;
     tens digit:
     (arr[j] % 100) / 10;
     hundreds digit:
     (arr[j] % 1000) / 100;
     ith digit from right:
     (arr[j] % (10^i)) / (10^(i-1))
     */

  int *C = (int *)malloc(sizeof(int) * (k + 1));
  int *B = (int *)malloc(sizeof(int) * n);
  for (int i = 0; i <= k; i++)
    C[i] = 0;
  for (int i = 0; i < n; i++)
    C[(arr[i] % (int)pow(10, d)) / (int)pow(10, d - 1)] += 1;
  for (int i = 1; i <= k; i++)
    C[i] = C[i] + C[i - 1];
  for (int i = n - 1; i >= 0; i--) {
    B[C[(arr[i] % (int)pow(10, d)) / (int)pow(10, d - 1)] - 1] = arr[i];
    C[(arr[i] % (int)pow(10, d)) / (int)pow(10, d - 1)] -= 1;
  }
  for (int i = 0; i < n; i++)
    arr[i] = B[i];

  free(C);
  free(B);
}

void radix_sort(int arr[], int n, int d) {
  for (int i = 1; i <= d; i++)
    count_sort(arr, n, 9, i);
}

int main(int argc, char *argv[]) {
  int A[N] = {84, 76, 12, 89, 55, 46, 98, 12, 14, 10, 29, 36, 45};
  radix_sort(A, N, 2);
  for (int i = 0; i < N; i++)
    printf("%d ", A[i]);
  printf("\n");

  return 0;
}
