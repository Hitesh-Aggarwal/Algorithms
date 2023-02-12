#include "countsort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  int A[] = {2, 5, 3, 0, 2, 3, 0, 3};
  int k = 5;
  int n = sizeof(A) / sizeof(int);
  for (int i = 0; i < n; i++)
    printf("%d  ", A[i]);
  printf("\n");
  count_sort(A, n, k);
  for (int i = 0; i < n; i++)
    printf("%d  ", A[i]);
  printf("\n");
  return 0;
}
