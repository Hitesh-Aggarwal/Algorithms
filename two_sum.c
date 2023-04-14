#include <stdio.h>
#include <stdlib.h>
#define N 10

int compare(const void *a, const void *b) {
  if ((*(int *)a) < (*(int *)b))
    return -1;
  else if ((*(int *)a) > (*(int *)b))
    return 1;
  return 0;
}

void two_sum(int arr[], int n, int x) {
  int i = 0;
  int j = n - 1;
  int val;
  while (i < j) {
    val = arr[i] + arr[j];
    if (val == x) {
      printf("%d and %d\n", arr[i], arr[j]);
      return;
    } else if (val > x)
      j--;
    else
      i++;
  }
  printf("Numbers do not exist\n");
}

int main(int argc, char *argv[]) {
  int arr[N] = {31, 71, 1, 41, 11, 51, 21, 91, 61, 81};
  qsort(arr, N, sizeof(int), compare);

  two_sum(arr,N,52);
  return 0;
}
