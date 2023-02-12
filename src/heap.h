#ifndef HEAP_H
#define HEAP_H

struct Heap {
  int *arr;
  int size;
};

void createHeap(struct Heap *h, int max_size);
void MaxHeapify(struct Heap *h, int i);
void MinHeapify(struct Heap *h, int i);
void MaxHeapify_iterative(struct Heap *h, int i);
void MinHeapify_iterative(struct Heap *h, int i);
void build_max_heap(struct Heap *h);
void printHeap(struct Heap *h);

#endif /* HEAP_H */

