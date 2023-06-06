#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

#define N 8

void DFS_Visit(vertex graph[],
               int u,
               char color[],
               int predecessor[],
               int discovery[],
               int finish[],
               int *time,
               int enable_print) {
  *time = *time + 1;
  discovery[u] = *time;
  color[u] = 'G';
  vertex *v = graph[u].next;
  while (v) {
    if (color[v->index] == 'W') {
      predecessor[v->index] = u;
      DFS_Visit(graph, v->index, color, predecessor, discovery, finish, time, enable_print);
    }
    v = v->next;
  }
  color[u] = 'B';
  *time = *time + 1;
  finish[u] = *time;
  if (enable_print) printf("%d ", u);
}

int *DFS(vertex graph[], int n, int *order, int enable_print) {
  char color[n];
  int predecessor[n];
  int discovery[n];
  int *finish = malloc(sizeof(int) * n);
  for (int i = 0; i < n; i++) {
    color[i] = 'W';
    predecessor[i] = -1;
  }
  int time = 0;
  int counter = 1;
  if (!order) {
    for (int i = 0; i < n; i++) {
      if (color[i] == 'W') {
        if (enable_print) printf("SCC %d: ", counter++);
        DFS_Visit(graph, i, color, predecessor, discovery, finish, &time, enable_print);
        if (enable_print) printf("\n");
      }
    }
  } else {
    for (int i = 0; i < n; i++) {
      if (color[order[i]] == 'W') {
        if (enable_print) printf("SCC %d: ", counter++);
        DFS_Visit(graph, order[i], color, predecessor, discovery, finish, &time, enable_print);
        if (enable_print) printf("\n");
      }
    }
  }
  return finish;
}

void strongly_connected_components(vertex *graph, int n) {
  int *finish = DFS(graph, n, NULL, 0);
  vertex *t_graph = transpose(graph, n);
  int order[n];
  int max;
  int max_index;
  for (int i = 0; i < n; i++) {
    max = finish[0];
    max_index = 0;
    for (int j = 0; j < n; j++) {
      if (finish[j] > max) {
        max = finish[j];
        max_index = j;
      }
    }
    finish[max_index] = -1;
    order[max_index] = i;
  }
  int *finish2 = DFS(t_graph, n, order, 1);
  free(t_graph);
  free(finish);
  free(finish2);
}

int main(int argc, char *argv[]) {
  vertex graph[N];
  for (int i = 0; i < N; i++) {
    graph[i].index = i;
    graph[i].next = NULL;
  }
  insert_edge(graph, 0, 1);
  insert_edge(graph, 1, 4);
  insert_edge(graph, 1, 5);
  insert_edge(graph, 1, 2);
  insert_edge(graph, 2, 3);
  insert_edge(graph, 2, 6);
  insert_edge(graph, 3, 2);
  insert_edge(graph, 3, 7);
  insert_edge(graph, 4, 5);
  insert_edge(graph, 4, 0);
  insert_edge(graph, 5, 6);
  insert_edge(graph, 6, 5);
  insert_edge(graph, 6, 7);
  insert_edge(graph, 7, 7);
  // DFS(graph, N, order);
  strongly_connected_components(graph, N);
  free_graph(graph, N);
  return EXIT_SUCCESS;
}
