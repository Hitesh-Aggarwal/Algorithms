#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define N 10

void merge(int arr[], int p, int q, int r) {
  int n1 = q - p + 1;
  int n2 = r - q;
  int *L = malloc(sizeof(int) * (n1 + 1));
  int *R = malloc(sizeof(int) * (n2 + 1));

  int i;
  int j;
  for (i = 0; i < n1; i++)
    L[i] = arr[p + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[q + j + 1];

  L[n1] = INT_MAX;
  R[n2] = INT_MAX;

  i = 0;
  j = 0;

  for (int k = p; k <= r; k++) {
    if (L[i] <= R[j])
      arr[k] = L[i++];
    else
      arr[k] = R[j++];
  }

  free(L);
  free(R);
}

void merge_sort(int arr[], int p, int r) {
  if (p < r) {
    int q = p + (r - p) / 2;
    merge_sort(arr, p, q);
    merge_sort(arr, q + 1, r);
    merge(arr, p, q, r);
  }
}

int main(int argc, char *argv[]) {
  int arr[N] = {31, 71, 1, 41, 11, 51, 21, 91, 61, 81};
  merge_sort(arr, 0, N - 1);
  for (int i = 0; i < N; i++)
    printf("%d ", arr[i]);
  printf("\n");
  return 0;
}
