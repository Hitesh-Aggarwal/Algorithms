#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

#define N 14

vertex *append_front(vertex *list, int u) {
  vertex *x = create_vertex(u);
  if (list == NULL)
    list = x;
  else {
    x->next = list;
    list = x;
  }
  return list;
}

void DFS_Visit(vertex graph[],
               int u,
               char color[],
               int predecessor[],
               int discovery[],
               int finish[],
               int *time,
               vertex **list) {
  *time = *time + 1;
  discovery[u] = *time;
  color[u] = 'G';
  vertex *v = graph[u].next;
  while (v) {
    if (color[v->index] == 'W') {
      predecessor[v->index] = u;
      DFS_Visit(graph, v->index, color, predecessor, discovery, finish, time, list);
    }
    v = v->next;
  }
  color[u] = 'B';
  *time = *time + 1;
  finish[u] = *time;
  *list = append_front(*list, u);
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
  vertex *list = NULL;
  for (int i = 0; i < n; i++) {
    if (color[i] == 'W') DFS_Visit(graph, i, color, predecessor, discovery, finish, &time, &list);
  }
  printf("Node\tPredecessor\tDiscovery_time\tFinish_time\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t%d\t\t%d\t\t%d\n", i, predecessor[i], discovery[i], finish[i]);
  }
  vertex *x = list;
  printf("Toplogical Sort: ");
  while (x) {
    list = x;
    printf("%d ", x->index);
    x = x->next;
    free(list);
  }
}

int main(int argc, char *argv[]) {
  vertex graph[N];
  for (int i = 0; i < N; i++) {
    graph[i].index = i;
    graph[i].next = NULL;
  }
  insert_edge(graph, 0, 4);
  insert_edge(graph, 0, 5);
  insert_edge(graph, 0, 11);
  insert_edge(graph, 1, 4);
  insert_edge(graph, 1, 8);
  insert_edge(graph, 1, 2);
  insert_edge(graph, 2, 5);
  insert_edge(graph, 2, 6);
  insert_edge(graph, 3, 2);
  insert_edge(graph, 3, 6);
  insert_edge(graph, 3, 13);
  insert_edge(graph, 4, 7);
  insert_edge(graph, 5, 8);
  insert_edge(graph, 5, 12);
  insert_edge(graph, 6, 5);
  insert_edge(graph, 8, 7);
  insert_edge(graph, 9, 10);
  insert_edge(graph, 9, 11);
  insert_edge(graph, 10, 13);
  insert_edge(graph, 12, 9);
  DFS(graph, N);
  free_graph(graph, N);
  return EXIT_SUCCESS;
}
