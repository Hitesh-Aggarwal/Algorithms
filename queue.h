#ifndef QUEUE_H
#define QUEUE_H

typedef struct Queue {
  void **arr;
  int f;
  int CAP;  // total capacity
  int size; // current size
} Queue;

#define is_empty(q) (q->size == 0)
#define is_full(q) (q->size == q->CAP)

Queue *make_queue(int cap);
void enqueue(Queue *q, void *x);
void *dequeue(Queue *q);
void free_queue(Queue *q);
#endif /* QUEUE_H */
