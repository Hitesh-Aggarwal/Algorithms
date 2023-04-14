#include <stdio.h>
#include <stdlib.h>
#define N 10

void insertion_sort_recursive(int *A, int i, int n) {
  if (i < n) {
    int val = A[i];
    int j = i - 1;
    while (j >= 0 && A[j] > val) {
      A[j + 1] = A[j];
      j = j - 1;
    }
    A[j + 1] = val;
    insertion_sort_recursive(A, i + 1, n);
  }
}

void insertion_sort(int *A, int n) {
  int i;
  int temp;
  for (int j = 1; j < n; j++) {
    temp = A[j];
    i = j - 1;
    while (i >= 0 && A[i] > temp) {
      A[i + 1] = A[i];
      i--;
    }
    A[i + 1] = temp;
  }
}

int main(int argc, char *argv[]) {
  int A[N] = {24, 15, 903, -23, 52, -523, 32, 54, -24, 12};
  insertion_sort_recursive(A, 0, N);
  for (int i = 0; i < N; i++)
    printf("%d ", A[i]);
  printf("\n");
  return 0;
}
