#ifndef GRAPH_H
#define GRAPH_H

typedef struct vertex {
  int index;
  struct vertex *next;
} vertex;

typedef struct queue {
  int cap;
  int size;
  int *arr;
  int q_front;
} queue;
vertex *create_vertex(int index);
vertex *transpose(vertex* graph, int n);
void insert_edge(vertex graph[], int u, int v);
void free_graph(vertex graph[], int n);
void enqueue(queue *q, int val);
int dequeue(queue *q);
#endif /* GRAPH_H */
