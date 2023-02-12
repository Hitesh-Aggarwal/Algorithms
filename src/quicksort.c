#include "quicksort.h"
#include <stdlib.h>

int partition(int *A, int p, int r) {
  int x = A[r];
  int temp;
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
  return i+1;
}

int randomPartition(int *A, int p, int r) {
  int i = (rand() % (r-p+1)) + p;
  int temp = A[i];
  A[i] = A[r];
  A[r] = temp;
  return partition(A,p,r);
}

void quicksort(int *A, int p, int r) {
  if (p < r) {
    int q = partition(A, p, r);
    quicksort(A, p, q - 1);
    quicksort(A, q + 1, r);
  }
}

void randomizedQuicksort(int *A, int p, int r) {
  if (p < r) {
    int q = randomPartition(A, p, r);
    randomizedQuicksort(A, p, q - 1);
    randomizedQuicksort(A, q + 1, r);
  }
}
