#include "graph.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define N 6

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

void DFS_Visit(vertex graph[], int u, char color[], int finish[], int *time, vertex **list) {
  color[u] = 'G';
  vertex *v = graph[u].next;
  while (v) {
    if (color[v->index] == 'W') DFS_Visit(graph, v->index, color, finish, time, list);
    v = v->next;
  }
  color[u] = 'B';
  *time = *time + 1;
  finish[u] = *time;
  *list = append_front(*list, u);
}

vertex *DFS(vertex graph[], int n) {
  char color[n];
  int finish[n];
  for (int i = 0; i < n; i++)
    color[i] = 'W';
  int time = 0;
  vertex *list = NULL;
  for (int i = 0; i < n; i++) {
    if (color[i] == 'W') DFS_Visit(graph, i, color, finish, &time, &list);
  }
  return list;
}

void relax(int u, int v, int w, int *d, int *p) {
  if (d[u] == INT_MAX) return;
  if (d[v] > d[u] + w) {
    d[v] = d[u] + w;
    p[v] = u;
  }
}

void dag_shortest_paths(vertex *graph, int s) {
  int d[N];
  int p[N];
  for (int i = 0; i < N; i++) {
    d[i] = INT_MAX;
    p[i] = -1;
  }
  d[s] = 0;
  vertex *list = DFS(graph, N);
  vertex *x = list;
  while (x) {
    vertex *v = graph[x->index].next;
    while (v) {
      relax(x->index, v->index, v->weight, d, p);
      v = v->next;
    }
    x = x->next;
  }
  printf("\nNode\t Predecessor\tDistanceFromSource\n");
  for (int i = 0; i < N; i++)
    printf("%d\t%d\t\t%d\n", i, p[i], d[i]);

  vertex *y = list;
  while (y) {
    list = y;
    y = y->next;
    free(list);
  }
}

int main(int argc, char *argv[]) {
  vertex graph[N];
  for (int i = 0; i < N; i++) {
    graph[i].index = i;
    graph[i].next = NULL;
    graph[i].weight = 0;
  }
  insert_weighted_edge(graph, 0, 2, 3);
  insert_weighted_edge(graph, 0, 1, 5);
  insert_weighted_edge(graph, 1, 3, 6);
  insert_weighted_edge(graph, 1, 2, 2);
  insert_weighted_edge(graph, 2, 5, 2);
  insert_weighted_edge(graph, 2, 4, 4);
  insert_weighted_edge(graph, 2, 3, 7);
  insert_weighted_edge(graph, 3, 5, 1);
  insert_weighted_edge(graph, 3, 4, -1);
  insert_weighted_edge(graph, 4, 5, -2);

  dag_shortest_paths(graph, 1);
  free_graph(graph, N);
  return EXIT_SUCCESS;
}
