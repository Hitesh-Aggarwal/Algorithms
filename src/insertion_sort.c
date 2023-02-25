#include "insertion_sort.h"
#include <stdlib.h>

void insertion_sort(int *A, int n) {
  int i;
  int temp;
  for (int j = 1; j < n; j++) {
    temp = A[j];
    i = j - 1;
    while (i >= 0 && A[i] > temp)
      A[i + 1] = A[i];
    A[i + 1] = temp;
  }
}
