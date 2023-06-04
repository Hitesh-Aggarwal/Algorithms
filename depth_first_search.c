#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

#define N 6

void DFS_Visit(vertex graph[],
               int u,
               char color[],
               int predecessor[],
               int discovery[],
               int finish[],
               int *time) {
  *time = *time + 1;
  discovery[u] = *time;
  color[u] = 'G';
  vertex *v = graph[u].next;
  while (v) {
    if (color[v->index] == 'W') {
      predecessor[v->index] = u;
      DFS_Visit(graph, v->index, color, predecessor, discovery, finish, time);
    }
    v = v->next;
  }
  color[u] = 'B';
  *time = *time + 1;
  finish[u] = *time;
}

void DFS(vertex graph[], int n) {
  char color[n];
  int predecessor[n];
  int discovery[n];
  int finish[n];
  for (int i = 0; i < n; i++) {
    color[i] = 'W';
    predecessor[i] = -1;
  }
  int time = 0;
  for (int i = 0; i < n; i++) {
    if (color[i] == 'W') DFS_Visit(graph, i, color, predecessor, discovery, finish, &time);
  }
  printf("Node\tPredecessor\tDiscovery_time\tFinish_time\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t%d\t\t%d\t\t%d\n", i,predecessor[i],discovery[i],finish[i]);
  }
}

int main(int argc, char *argv[]) {
  vertex graph[N];
  for (int i = 0; i < N; i++) {
    graph[i].index = i;
    graph[i].next = NULL;
  }
  insert_edge(graph, 0, 3);
  insert_edge(graph, 0, 1);
  insert_edge(graph, 1, 4);
  insert_edge(graph, 2, 5);
  insert_edge(graph, 2, 4);
  insert_edge(graph, 3, 1);
  insert_edge(graph, 4, 3);
  insert_edge(graph, 5, 5);
  DFS(graph, N);
  free_graph(graph, N);
  return EXIT_SUCCESS;
}
