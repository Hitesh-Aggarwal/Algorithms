#include "graph.h"
#include "priority_queue.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5

void relax(int u, int v, int w, int *d, int *p) {
  if (d[u] == INT_MAX) return;
  if (d[v] > d[u] + w) {
    d[v] = d[u] + w;
    p[v] = u;
  }
}

void dijkastra(vertex *graph, int s) {
  int d[N];
  int p[N];
  vertex final_graph[N];
  for (int i = 0; i < N; i++) {
    final_graph[i].next = 0;
    final_graph[i].weight = 0;
    final_graph[i].index = i;
    d[i] = INT_MAX;
    p[i] = -1;
  }
  d[s] = 0;
  int *pointer[N]; // priority queue stores void * pointers.
  for (int i = 0; i < N; i++) {
    pointer[i] = malloc(sizeof(int));
    *pointer[i] = i;
  }
  PQ *q = create_queue(N);
  for (int i = 0; i < N; i++)
    min_heap_insert(q, pointer[i], d[i]);
  while (!is_empty(q)) {
    int *u = heap_extract_min(q);
    vertex *v = graph[*u].next;
    while (v) {
      relax(*u, v->index, v->weight, d, p);
      v = v->next;
    }
  }
  for (int i = 0; i < N; i++) {
    if (i == s) continue;
    insert_edge(final_graph, p[i], i);
  }
  pretty_print_dfs(final_graph, N);
  free_memory(q);
  free_graph(final_graph, N);
  for (int i = 0; i < N; i++)
    free(pointer[i]);
}

int main(int argc, char *argv[]) {
  vertex graph[N];
  for (int i = 0; i < N; i++) {
    graph[i].index = i;
    graph[i].weight = 0;
    graph[i].next = NULL;
  }
  insert_weighted_edge(graph, 0, 4, 5);
  insert_weighted_edge(graph, 0, 1, 10);
  insert_weighted_edge(graph, 1, 4, 2);
  insert_weighted_edge(graph, 1, 2, 1);
  insert_weighted_edge(graph, 2, 3, 4);
  insert_weighted_edge(graph, 3, 2, 6);
  insert_weighted_edge(graph, 3, 0, 7);
  insert_weighted_edge(graph, 4, 3, 2);
  insert_weighted_edge(graph, 4, 2, 9);
  insert_weighted_edge(graph, 4, 1, 3);
  dijkastra(graph, 0);
  free_graph(graph, N);
  return EXIT_SUCCESS;
}
