#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define N 8

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

void BFS(vertex graph[], int n, int s) {
  char color[n];
  int dist[n];
  int predecessor[n];
  queue Q;
  Q.arr = malloc(sizeof(int) * n);
  Q.size = 0;
  Q.cap = n;
  Q.q_front = -1;

  for (int i = 0; i < n; i++) {
    if (i == s) continue;
    color[i] = 'W';
    dist[i] = INT_MAX;
    predecessor[i] = -1;
  }
  color[s] = 'G';
  dist[s] = 0;
  predecessor[s] = -1;
  enqueue(&Q, s);
  while (Q.size > 0) {
    int u = dequeue(&Q);
    vertex *p = graph[u].next;
    while (p != NULL) {
      if (color[p->index] == 'W') {
        color[p->index] = 'G';
        dist[p->index] = dist[u] + 1;
        predecessor[p->index] = u;
        enqueue(&Q, p->index);
      }
      p = p->next;
    }
    color[u] = 'B';
    printf("Node: %d\t\tPredecessor: %d\t\tDistance from source: %d\n", u, predecessor[u],dist[u]);
  }
  free(Q.arr);
}

int main(int argc, char *argv[]) {
  vertex graph[N];
  for (int i = 0; i < N; i++) {
    graph[i].index = i;
    graph[i].next = NULL;
  }
  insert_edge(graph, 0, 1);
  insert_edge(graph, 0, 4);
  insert_edge(graph, 1, 0);
  insert_edge(graph, 1, 5);
  insert_edge(graph, 2, 3);
  insert_edge(graph, 2, 5);
  insert_edge(graph, 2, 6);
  insert_edge(graph, 3, 2);
  insert_edge(graph, 3, 6);
  insert_edge(graph, 3, 7);
  insert_edge(graph, 4, 0);
  insert_edge(graph, 5, 1);
  insert_edge(graph, 5, 2);
  insert_edge(graph, 5, 6);
  insert_edge(graph, 6, 7);
  insert_edge(graph, 6, 5);
  insert_edge(graph, 6, 2);
  insert_edge(graph, 6, 3);
  insert_edge(graph, 7, 3);
  insert_edge(graph, 7, 6);
  BFS(graph, N, 0);
  free_graph(graph, N);
  return EXIT_SUCCESS;
}
