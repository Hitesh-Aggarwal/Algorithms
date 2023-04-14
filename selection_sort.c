#include <limits.h>
#include <stdio.h>
#define N 10

void selection_sort(int arr[], int n) {
  int min;
  int i = 0;
  int temp;
  while (i < n - 1) {
    min = i+1;
    for (int j = i + 1; j < n; j++)
      if (arr[j] < arr[min]) min = j;
    temp = arr[min];
    arr[min] = arr[i];
    arr[i++] = temp;
  }
}

int main(int argc, char *argv[]) {
  int arr[N] = {31, 71, 1, 41, 11, 51, 21, 91, 61, 81};
  selection_sort(arr, N);
  for (int i = 0; i < N; i++)
    printf("%d ", arr[i]);
  printf("\n");
  return 0;
}
