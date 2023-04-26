#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100
#define parent(i) ((i + 1) / 2 - 1)
#define left(i) ((2 * (i + 1) - 1))
#define right(i) (2 * (i + 1))
#define heap_maximum(arr) (*arr)
#define is_empty(pq) (pq.heap_size == 0)

typedef struct PQ {
  int *arr;
  int heap_size;
  int length;
} PQ;

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

int heap_extract_max(PQ *pq) {
  if (pq->heap_size < 1) {
    printf("Heap underflow");
    return INT_MAX;
  }
  int max = heap_maximum(pq->arr);
  pq->arr[0] = pq->arr[pq->heap_size - 1];
  pq->heap_size = pq->heap_size - 1;
  MaxHeapify(pq->arr, pq->heap_size, 0);
  return max;
}

void Heap_increase_key(PQ *pq, int i, int k) {
  if (i >= pq->heap_size) return;
  if (k < pq->arr[i]) {
    printf("new key smaller than current key");
    return;
  }
  pq->arr[i] = k;
  int temp = pq->arr[i];
  while (i > 0 && pq->arr[parent(i)] < temp) {
    pq->arr[i] = pq->arr[parent(i)];
    i = parent(i);
  }
  pq->arr[i] = temp;
}

void max_heap_insert(PQ *pq, int k) {
  if (pq->heap_size >= pq->length){
    printf("Heap Overflow");
    return;
  }
  pq->arr[pq->heap_size] = INT_MIN;
  pq->heap_size = pq->heap_size + 1;
  Heap_increase_key(pq,pq->heap_size-1,k);
}

int main(int argc, char *argv[]) {
  PQ pq;
  pq.length = N;
  pq.arr = malloc(sizeof(int)*pq.length);
  max_heap_insert(&pq,80);
  max_heap_insert(&pq,70);
  max_heap_insert(&pq,90);
  max_heap_insert(&pq,85);
  max_heap_insert(&pq,10);
  max_heap_insert(&pq,30);
  while (!is_empty(pq))
    printf("%d ", heap_extract_max(&pq));
  return 0;
}
