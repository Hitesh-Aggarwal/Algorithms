#ifndef HEAP_H
#define HEAP_H

typedef struct Heap {
  int *arr;
  int size;
} Heap;

void createHeap(Heap *h, int max_size);
void MaxHeapify(Heap *h, int i);
void MinHeapify(Heap *h, int i);
void MaxHeapify_iterative(Heap *h, int i);
void MinHeapify_iterative(Heap *h, int i);
void build_max_heap(Heap *h);
void build_min_heap(Heap *h);
void printHeap(Heap *h);

#endif /* HEAP_H */

