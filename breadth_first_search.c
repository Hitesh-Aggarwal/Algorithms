#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define N 8

void BFS(vertex graph[], int n, int s) {
  char color[n];
  int dist[n];
  int predecessor[n];
  queue Q;
  Q.arr = malloc(sizeof(int) * n);
  Q.size = 0;
  Q.cap = n;
  Q.q_front = 0;

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
    printf("Node: %d\t\tPredecessor: %d\t\tDistance from source: %d\n", u, predecessor[u], dist[u]);
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
