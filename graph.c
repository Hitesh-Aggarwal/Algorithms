#include "graph.h"
#include <stdlib.h>
#include <limits.h>

vertex *create_vertex(int index) {
  vertex *x = malloc(sizeof(vertex));
  x->index = index;
  x->next = NULL;
  return x;
}

void insert_edge(vertex graph[], int u, int v) {
  vertex *x = create_vertex(v);
  x->next = graph[u].next;
  graph[u].next = x;
}

void free_graph(vertex graph[], int n) {
  for (int i = 0; i < n; i++) {
    vertex *p = graph[i].next;
    while (p) {
      graph[i].next = p->next;
      free(p);
      p = graph[i].next;
    }
  }
}

void enqueue(queue *q, int val) {
  if (q->size == q->cap) return;
  int index = (q->q_front + q->size) % q->cap;
  q->size += 1;
  q->arr[index] = val;
}

int dequeue(queue *q) {
  if (q->size == 0) return INT_MIN;
  int val = q->arr[q->q_front];
  q->q_front = (q->q_front + 1) % q->cap;
  q->size = q->size - 1;
  return val;
}

vertex *transpose(vertex *graph, int n){
  vertex *t_graph = malloc(sizeof(vertex)*n);
  for(int i=0; i<n; i++){
    vertex *p = graph[i].next;
    while(p){
      insert_edge(t_graph,p->index,i);
      p = p->next;
    }
  }
  return t_graph;
}
