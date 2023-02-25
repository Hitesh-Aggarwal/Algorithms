#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10

typedef struct Heap {
  int *arr;
  int size;
} Heap;

int parent(int i) { return ((i + 1) / 2) - 1; }

int left(int i) { return 2 * (i + 1) - 1; }

int right(int i) { return 2 * (i + 1); }

void createHeap(Heap *h, int max_size) {
  h->arr = (int *)malloc(sizeof(int) * max_size);
  h->size = 0;
}

void MaxHeapify(Heap *h, int i) {
  int l = left(i);
  int r = right(i);
  int largest = l;
  int temp;
  if (l < h->size && h->arr[l] > h->arr[i])
    largest = l;
  else
    largest = i;
  if (r < h->size && h->arr[r] > h->arr[largest])
    largest = r;
  if (largest != i) {
    temp = h->arr[i];
    h->arr[i] = h->arr[largest];
    h->arr[largest] = temp;
    MaxHeapify(h, largest);
  }
}

void MaxHeapify_iterative(Heap *h, int i) {
  int largest = i;
  int temp;
  while (1) {
    int l = left(i);
    int r = right(i);
    if (l < h->size && h->arr[l] > h->arr[i])
      largest = l;
    else
      largest = i;
    if (r < h->size && h->arr[r] > h->arr[largest])
      largest = r;
    if (largest == i)
      break;
    else {
      temp = h->arr[i];
      h->arr[i] = h->arr[largest];
      h->arr[largest] = temp;
      i = largest;
    }
  }
}

void build_max_heap(Heap *h) {
  for (int i = h->size / 2 - 1; i >= 0; i--)
    MaxHeapify_iterative(h, i);
}

void printHeap(Heap *h) {
  int k = 0;
  for (int size = 1; k < h->size; size *= 2) {
    for (int c = 0; c < size && k < h->size; c++)
      printf("%d ", h->arr[k++]);
    printf("\n");
  }
}

void heapSort(Heap *h) {
  int orig_size = h->size;
  int temp;
  build_max_heap(h);
  for (int i = h->size - 1; i >= 0; i--) {
    temp = h->arr[i];
    h->arr[i] = h->arr[0];
    h->arr[0] = temp;
    h->size = h->size - 1;
    MaxHeapify(h, 0);
  }
  h->size = orig_size;
}

int heap_maximum(Heap *h) { return h->arr[0]; }

int heap_extract_max(Heap *h) {
  if (h->size < 1) {
    printf("Heap underflow");
    return -1;
  }
  int max = h->arr[0];
  h->arr[0] = h->arr[h->size - 1];
  h->size = h->size - 1;
  MaxHeapify(h, 0);
  return max;
}

void Heap_increase_key(Heap *h, int i, int k) {
  if (i >= h->size)
    return;
  if (k < h->arr[i]) {
    printf("new key smaller than current key");
    return;
  }
  h->arr[i] = k;
  int temp = h->arr[i];
  while (i > 0 && h->arr[parent(i)] < temp) {
    h->arr[i] = h->arr[parent(i)];
    i = parent(i);
  }
  h->arr[i] = temp;
}

void max_heap_insert(Heap *h, int k) {
  h->size = h->size + 1;
  h->arr[h->size - 1] = INT_MIN;
  Heap_increase_key(h, h->size - 1, k);
}

void heap_delete(Heap *h, int i) {
  if (i >= h->size)
    return;
  h->arr[i] = h->arr[h->size - 1];
  h->size = h->size - 1;
  MaxHeapify(h, i);
}

int main(int argc, char *argv[]) {
  int A[N] = {24, 15, 903, -23, 52, -523, 32, 54, -24, 12};
  Heap *h = (Heap *)malloc(sizeof(Heap));
  h->arr = A;
  h->size = N;
  build_max_heap(h);
  printHeap(h);
  return 0;
}
