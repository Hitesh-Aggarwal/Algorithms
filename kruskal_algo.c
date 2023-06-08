#include "disjoint_sets.h"
#include "graph.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define N 9

void kruskal(int graph[N][N]) {
  vertex final_graph[N];
  for (int i = 0; i < N; i++) {
    final_graph[i].index = i;
    final_graph[i].next = NULL;
  }
  initialize_sets(N);
  for (int i = 0; i < N; i++)
    make_set(i);
  int u = 0, v = 1;
  int min;
  int edge_count = 0;
  while (edge_count < N - 1) {
    min = INT_MAX;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (find_set(i) != find_set(j) && graph[i][j] < min) {
          min = graph[i][j];
          u = i;
          v = j;
        }
      }
    }
    Union(u, v);
    edge_count = edge_count + 1;
    insert_edge(final_graph, u, v);
    insert_edge(final_graph, v, u);
    printf("Edge Selected: %d --- %d\n", u, v);
  }
  printf("\nFinal Tree:\n");
  pretty_print_dfs(final_graph, N);
  free_graph(final_graph, N);
  destroy_sets();
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
  kruskal(graph);
  return 0;
}
