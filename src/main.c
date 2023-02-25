#include "countsort.h"
#include "min_max.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int A[] = {2, 5, 3, 10, 2, -3, 0, 3};
  int n = sizeof(A) / sizeof(int);
  int min, max;
  min_and_max(A, n, &min, &max);
  printf("%d %d\n", min, max);
  return 0;
}
