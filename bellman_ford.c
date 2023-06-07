#include "graph.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5

void relax(int w[N][N], int u, int v, int *d, int *p) {
  if (d[v] > d[u] + w[u][v]) {
    d[v] = d[u] + w[u][v];
    p[v] = u;
  }
}

void bellman_ford(int w[N][N], int s) {
  vertex final_graph[N];
  for (int i = 0; i < N; i++) {
    final_graph[i].next = NULL;
    final_graph[i].index = i;
  }

  int d[N]; // upper bound on weight of shortest path from s to every vertex.
  int p[N]; // stores predecessor of every vertex.
  for (int i = 0; i < N; i++) {
    d[i] = INT_MAX;
    p[i] = -1;
  }
  d[s] = 0;
  for (int i = 0; i < N - 1; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        if (j != k && w[j][k] < INT_MAX) relax(w, j, k, d, p);
      }
    }
  }
  for (int j = 0; j < N; j++) {
    for (int k = 0; k < N; k++) {
      if (w[j][k] > 0 && w[j][k] < INT_MAX) {
        if (d[k] > d[j] + w[j][k]) {
          printf("Negative weight cycle found\n");
          return;
        }
      }
    }
  }
  for (int i = 0; i < N; i++) {
    if (i == s) continue;
    insert_edge(final_graph, p[i], i);
  }
  printf("\n");
  pretty_print_dfs(final_graph, N);
  free_graph(final_graph, N);
}
int main(int argc, char *argv[]) {
  int w[N][N] = {{0, 6, INT_MAX, INT_MAX, 7},
                 {INT_MAX, 0, 5, -4, 8},
                 {INT_MAX, -2, 0, INT_MAX, INT_MAX},
                 {2, INT_MAX, 7, 0, INT_MAX},
                 {INT_MAX, INT_MAX, -3, 9, 0}};
  bellman_ford(w, 0);

  return 0;
}
