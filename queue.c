#include "queue.h"
#include <stdlib.h>

Queue *make_queue(int cap) {
  Queue *q = malloc(sizeof(Queue));
  q->f = 0;
  q->size = 0;
  q->CAP = cap;
  q->arr = malloc(sizeof(void *) * cap);
  for (int i = 0; i < cap; i++)
    q->arr[i] = NULL;
  return q;
}

void enqueue(Queue *q, void *x) {
  if (is_full(q)) return;
  q->arr[(q->f + q->size) % q->CAP] = x;
  q->size = q->size + 1;
}

void *dequeue(Queue *q) {
  if (is_empty(q)) return NULL;
  void *x = q->arr[q->f];
  q->f = (q->f + 1) % q->CAP;
  q->size = (q->size - 1 + q->CAP) % q->CAP;
  return x;
}

void free_queue(Queue *q) {
  free(q->arr);
  free(q);
}
