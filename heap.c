#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10
#define parent(i) ((i + 1) / 2 - 1)
#define left(i) ((2 * (i + 1) - 1))
#define right(i) (2 * (i + 1))
#define heap_maximum(arr) (*arr)

void MaxHeapify(int arr[], int n, int i) {
  int l = left(i);
  int r = right(i);
  int largest = l;
  int temp;
  if (l < n && arr[l] > arr[i])
    largest = l;
  else
    largest = i;
  if (r < n && arr[r] > arr[largest]) largest = r;
  if (largest != i) {
    temp = arr[i];
    arr[i] = arr[largest];
    arr[largest] = temp;
    MaxHeapify(arr, n, largest);
  }
}

void MaxHeapify_iterative(int arr[], int n, int i) {
  int largest = i;
  int temp;
  while (1) {
    int l = left(i);
    int r = right(i);
    if (l < n && arr[l] > arr[i])
      largest = l;
    else
      largest = i;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest == i)
      break;
    else {
      temp = arr[i];
      arr[i] = arr[largest];
      arr[largest] = temp;
      i = largest;
    }
  }
}

void build_max_heap(int arr[], int n) {
  for (int i = n / 2 - 1; i >= 0; i--)
    MaxHeapify_iterative(arr, n, i);
}

void heapSort(int arr[], int n) {
  int temp;
  build_max_heap(arr, n);
  for (int i = n - 1; i >= 0; i--) {
    temp = arr[i];
    arr[i] = arr[0];
    arr[0] = temp;
    n = n - 1;
    MaxHeapify(arr, n - 1, 0);
  }
}

int heap_extract_max(int arr[], int n) {
  if (n < 1) {
    printf("Heap underflow");
    return -1;
  }
  int max = heap_maximum(arr);
  arr[0] = arr[n - 1];
  n = n - 1;
  MaxHeapify(arr, n, 0);
  return max;
}

void Heap_increase_key(int arr[], int n, int i, int k) {
  if (i >= n) return;
  if (k < arr[i]) {
    printf("new key smaller than current key");
    return;
  }
  arr[i] = k;
  int temp = arr[i];
  while (i > 0 && arr[parent(i)] < temp) {
    arr[i] = arr[parent(i)];
    i = parent(i);
  }
  arr[i] = temp;
}

void max_heap_insert(int arr[], int n, int k) {
  arr[n] = INT_MIN;
  Heap_increase_key(arr, n + 1, n, k);
}

void heap_delete(int arr[],int n,int i) {
  if (i >= n) return;
  arr[i] = arr[n - 1];
  MaxHeapify(arr,n, i);
}

int main(int argc, char *argv[]) {
  int A[N] = {24, 15, 903, -23, 52, -523, 32, 54, -24, 12};
  heapSort(A,N);
  for (int i = 0; i < N; i++)
    printf("%d ", A[i]);
  printf("\n");
  return 0;
}
