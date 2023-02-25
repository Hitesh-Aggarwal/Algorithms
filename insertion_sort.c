#include <stdio.h>
#include <stdlib.h>
#define N 10

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
  insertion_sort(A, N);
  for (int i = 0; i < N; i++)
    printf("%d ", A[i]);
  printf("\n");
  return 0;
}
