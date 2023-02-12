#include "quicksort.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int A[] = {30, 34, 41, 6,  48, 36, 15, 42, 24, 47, 25, 9,  5,  50, 14, 20, 45,
             31, 18, 8,  43, 40, 17, 2,  21, 1,  23, 39, 27, 35, 7,  12, 44, 19,
             11, 13, 38, 49, 26, 16, 33, 10, 22, 37, 32, 29, 3,  28, 4,  46};
  int size = sizeof(A) / sizeof(int);
  for (int i = 0; i < size; i++)
    printf("%d  ", A[i]);
  printf("\n");
  randomizedQuicksort(A, 0, size - 1);
  for (int i = 0; i < size; i++)
    printf("%d  ", A[i]);
  printf("\n");
  return 0;
}
