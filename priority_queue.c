#include "priority_queue.h"
#include <limits.h>
#include <stdlib.h>

#define parent(i) ((i + 1) / 2 - 1)
#define left(i) ((2 * (i + 1) - 1))
#define right(i) (2 * (i + 1))

PQ *create_queue(int cap) {
  if (cap <= 0) return NULL;
  PQ *x = malloc(sizeof(PQ));
  x->arr = malloc(sizeof(node) * cap);
  for (int i = 0; i < cap; i++) {
    x->arr[i].key = INT_MAX;
    x->arr[i].obj = NULL;
  }
  x->capacity = cap;
  x->heap_size = 0;
  return x;
}

void *heap_minimum(PQ *queue) {
  if (is_empty(queue))
    return NULL;
  else
    return queue->arr[0].obj;
}

int is_present(PQ *queue, void *obj) {
  if (is_empty(queue)) return 0;
  for (int i = 0; i < queue->heap_size; i++)
    if (queue->arr[i].obj == obj) return 1;
  return 0;
}

void MinHeapify(PQ *queue, int i) {
  int l = left(i);
  int r = right(i);
  int s = l;
  node temp;
  if (l < queue->heap_size && queue->arr[l].key < queue->arr[i].key)
    s = l;
  else
    s = i;
  if (r < queue->heap_size && queue->arr[r].key < queue->arr[s].key) s = r;
  if (s != i) {
    temp = queue->arr[i];
    queue->arr[i] = queue->arr[s];
    queue->arr[s] = temp;
    MinHeapify(queue, s);
  }
}

void *heap_extract_min(PQ *pq) {
  if (is_empty(pq)) return NULL;
  void *min = heap_minimum(pq);
  pq->arr[0] = pq->arr[pq->heap_size - 1];
  pq->arr[pq->heap_size-1].key = INT_MAX;
  pq->arr[pq->heap_size-1].obj = NULL;
  pq->heap_size = pq->heap_size - 1;
  MinHeapify(pq, 0);
  return min;
}

void Heap_decrease_key_aux(PQ *pq, int i, int k) {
  if (i >= pq->heap_size) return;
  if (k >= pq->arr[i].key) return; // key is already smaller than k

  pq->arr[i].key = k;
  node temp = pq->arr[i];
  while (i >= 0 && pq->arr[parent(i)].key > temp.key) {
    pq->arr[i] = pq->arr[parent(i)];
    i = parent(i);
  }
  pq->arr[i] = temp;
}

void Heap_decrease_key(PQ *pq, void *obj, int k) {
  if (is_empty(pq)) return;
  for (int i = 0; i < pq->heap_size; i++)
    if (pq->arr[i].obj == obj) {
      Heap_decrease_key_aux(pq, i, k);
      return;
    }
}

void min_heap_insert(PQ *pq, void *obj, int k) {
  if (pq->heap_size >= pq->capacity) return;
  pq->arr[pq->heap_size].key = INT_MAX;
  pq->arr[pq->heap_size].obj = obj;
  pq->heap_size = pq->heap_size + 1;
  Heap_decrease_key_aux(pq, pq->heap_size - 1, k);
}

void free_memory(PQ *pq) {
  if (pq) {
    free(pq->arr);
    free(pq);
  }
}

int give_key(PQ *pq, void *obj) {
  if (is_empty(pq)) return INT_MAX;
  for (int i = 0; i < pq->heap_size; i++)
    if (pq->arr[i].obj == obj) return pq->arr[i].key;
  return INT_MAX;
}
