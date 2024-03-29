#include <stdio.h>
#include <stdlib.h>
#define N 10

int partition(int *A, int p, int r) {
  long x = A[r];
  long temp;
  int i = p - 1;
  for (int j = p; j <= r - 1; j++) {
    if (A[j] <= x) {
      i++;
      temp = A[i];
      A[i] = A[j];
      A[j] = temp;
    }
  }
  temp = A[i + 1];
  A[i + 1] = A[r];
  A[r] = temp;
  return i + 1;
}

int randomPartition(int *A, int p, int r) {
  int i = (rand() % (r - p + 1)) + p;
  long temp = A[i];
  A[i] = A[r];
  A[r] = temp;
  return partition(A, p, r);
}

int randomized_select(int *A, int p, int r, int i) {
  if (p == r) return A[p];
  int q = randomPartition(A, p, r);
  int k = q - p + 1;
  if (i == k)
    return A[q];
  else if (i < k)
    return randomized_select(A, p, q - 1, i);
  else
    return randomized_select(A, q + 1, r, i - k);
}

int randomized_select_iterative(int *A, int n, int i) {
  int p = 0;
  int r = n - 1;
  int q, k;
  while (p < r) {
    q = randomPartition(A, p, r);
    k = q - p + 1;
    if (i == k)
      return A[q];
    else if (i < k)
      r = q - 1;
    else {
      p = q + 1;
      i = i - k;
    }
  }
  return A[p];
}

int main(int argc, char *argv[]) {
  int A[N] = {24, 15, 903, -23, 52, -523, 32, 54, -24, 12};
  int i = 4;
  printf("%dth smallest element: %d\n", i, randomized_select_iterative(A, N, i));
  printf("\n");
  return 0;
}
