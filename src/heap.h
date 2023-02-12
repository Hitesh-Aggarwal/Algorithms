#ifndef HEAP_H
#define HEAP_H

typedef struct Heap {
  int *arr;
  int size;
} Heap;

void createHeap(Heap *h, int max_size);
void MaxHeapify(Heap *h, int i);
void MaxHeapify_iterative(Heap *h, int i);
void build_max_heap(Heap *h);
void printHeap(Heap *h);
void heapSort(Heap *h);
int heap_maximum(Heap *h);
int heap_extract_max(Heap *h);
void Heap_increase_key(Heap *h, int i, int k);
void max_heap_insert(Heap *h, int k);
void heap_delete(Heap *h, int i);
#endif /* HEAP_H */

