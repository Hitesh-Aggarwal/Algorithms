#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int arr[] = {3, 8, 10, 4, 7, 2, 5, 9, 6, 1};
  struct Heap *h = (struct Heap *)malloc(sizeof(struct Heap));
  h->arr = arr;
  h->size = 10;
  printHeap(h);
  build_max_heap(h);
  printHeap(h);
  return 0;
}
