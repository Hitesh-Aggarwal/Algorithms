#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

int parent(int i) { return ((i + 1) / 2) - 1; }

int left(int i) { return 2 * (i + 1) - 1; }

int right(int i) { return 2 * (i + 1); }

void createHeap(struct Heap *h, int max_size) {
  h->arr = (int *)malloc(sizeof(int) * max_size);
  h->size = 0;
}

void MaxHeapify(struct Heap *h, int i) {
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

void MinHeapify(struct Heap *h, int i) {
  int l = left(i);
  int r = right(i);
  int smallest = l;
  int temp;
  if (l < h->size && h->arr[l] < h->arr[i])
    smallest = l;
  else
    smallest = i;
  if (r < h->size && h->arr[r] < h->arr[smallest])
    smallest = r;
  if (smallest != i) {
    temp = h->arr[i];
    h->arr[i] = h->arr[smallest];
    h->arr[smallest] = temp;
    MaxHeapify(h, smallest);
  }
}

void MaxHeapify_iterative(struct Heap *h, int i) {
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

void MinHeapify_iterative(struct Heap *h, int i) {
  int smallest = i;
  int temp;
  while (1) {
    int l = left(i);
    int r = right(i);
    if (l < h->size && h->arr[l] < h->arr[i])
      smallest = l;
    else
      smallest = i;
    if (r < h->size && h->arr[r] < h->arr[smallest])
      smallest = r;
    if (smallest == i)
      break;
    else {
      temp = h->arr[i];
      h->arr[i] = h->arr[smallest];
      h->arr[smallest] = temp;
      i = smallest;
    }
  }
}

void build_max_heap(struct Heap *h) {
  for (int i = h->size / 2 - 1; i >= 0; i--)
    MaxHeapify_iterative(h, i);
}

void printHeap(struct Heap *h) {
  int k = 0;
  for (int size = 1; k < h->size; size *= 2) {
    for (int c = 0; c < size && k < h->size; c++)
      printf("%d ", h->arr[k++]);
    printf("\n");
  }
}
