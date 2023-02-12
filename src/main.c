#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int A[] = {5,3,17,10,84,19,6,22,9};
  Heap *h = (Heap *)malloc(sizeof(Heap));
  h->arr = A;
  h->size = 9;
  printHeap(h);
  build_max_heap(h);
  printHeap(h);
  return 0;
}
