#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define N 10

int inversions = 0;

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
    else {
      arr[k] = R[j++];
      inversions += (n1-i);
    }
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

int inversions_count_brute_force(int arr[], int n) {
  int inv = 0;
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (arr[i] > arr[j]) inv++;
    }
  }
  return inv;
}

int main(int argc, char *argv[]) {
  int arr[N] = {31, 71, 1, 41, 11, 51, 21, 91, 61, 81};
  printf("%d\n", inversions_count_brute_force(arr,N));
  merge_sort(arr, 0, N - 1);
  printf("%d\n", inversions);
  return 0;
}
