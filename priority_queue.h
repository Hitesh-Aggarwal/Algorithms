#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

typedef struct node {
  int key;
  void *obj;
} node;

typedef struct PQ {
  node *arr;
  int heap_size;
  int capacity;
} PQ;

PQ* create_queue(int cap);
int is_empty(PQ *queue);
int is_full(PQ *pq);
void *heap_minimum(PQ *queue);
int is_present(PQ *queue, void *obj);
void *heap_extract_min(PQ *pq);
void Heap_decrease_key(PQ *pq, void *obj, int k);
void min_heap_insert(PQ *pq, void *obj, int k);
void free_memory(PQ *pq);
int give_key(PQ *pq, void *obj);

#endif /* PRIORITY_QUEUE_H */
