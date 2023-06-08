#include "graph.h"
#include "priority_queue.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define N 9

void MST_prim(int graph[N][N]) {
  PQ *queue = create_queue(N);
  vertex final_graph[N];
  for (int i = 0; i < N; i++) {
    final_graph[i].next = NULL;
    final_graph[i].index = i;
  }

  // convert all integers to pointers so that we can store them in priority_queue
  // since the PQ stores only void *
  int *vertices[N];
  for (int i = 0; i < N; i++) {
    vertices[i] = malloc(sizeof(int));
    *vertices[i] = i;
  }
  int p[N]; // p[i] is predecessor of vertex i
  int k[N]; // key[i] is key of vertex i

  for (int i = 0; i < N; i++) {
    k[i] = INT_MAX;
    p[i] = -1;
  }

  k[0] = 0;
  for (int i = 0; i < N; i++)
    min_heap_insert(queue, vertices[i], k[i]);

  while (!is_empty(queue)) {
    int *u = heap_extract_min(queue);
    for (int i = 0; i < N; i++) {
      if (*u != i && graph[*u][i] != INT_MAX && is_present(queue, vertices[i]) &&
          graph[*u][i] < k[i]) {
        p[i] = *u;
        k[i] = graph[*u][i];
        Heap_decrease_key(queue, vertices[i], k[i]);
      }
    }
    if (*u > 0) {
      printf("\nEdge Selected: %d ---- %d", p[*u], *u);
      insert_edge(final_graph, *u, p[*u]);
      insert_edge(final_graph, p[*u], *u);
    }
  }
  printf("\n");
  pretty_print_dfs(final_graph, N);
  free_memory(queue);
  free_graph(final_graph, N);
  for (int i = 0; i < N; i++)
    free(vertices[i]);
}

int main(int argc, char *argv[]) {

  int graph[N][N] = {{0, 4, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 8, INT_MAX},
                     {4, 0, 8, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 11, INT_MAX},
                     {INT_MAX, 8, 0, 7, INT_MAX, 4, INT_MAX, INT_MAX, 2},
                     {INT_MAX, INT_MAX, 7, 0, 9, 14, INT_MAX, INT_MAX, INT_MAX},
                     {INT_MAX, INT_MAX, INT_MAX, 9, 0, 10, INT_MAX, INT_MAX, INT_MAX},
                     {INT_MAX, INT_MAX, 4, 14, 10, 0, 2, INT_MAX, INT_MAX},
                     {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 2, 0, 1, 6},
                     {8, 11, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 1, 0, 7},
                     {INT_MAX, INT_MAX, 2, INT_MAX, INT_MAX, INT_MAX, 6, 7, 0}};

  MST_prim(graph);
  return EXIT_SUCCESS;
}
