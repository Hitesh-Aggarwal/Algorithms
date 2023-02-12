#include "quicksort.h"
#include <stdlib.h>

int partition(long *A, int p, int r) {
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
  return i+1;
}

int randomPartition(long *A, int p, int r) {
  int i = (rand() % (r-p+1)) + p;
  long temp = A[i];
  A[i] = A[r];
  A[r] = temp;
  return partition(A,p,r);
}

void quicksort(long *A, int p, int r) {
  while (p < r) {
    int q = partition(A, p, r);
    quicksort(A, p, q - 1);
    p = q+1;
  }
}

void randomizedQuicksort(long *A, int p, int r) {
  while (p < r) {
    int q = randomPartition(A, p, r);
    randomizedQuicksort(A, p, q - 1);
    p = q+1;
  }
}
