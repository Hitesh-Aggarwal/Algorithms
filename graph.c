#include "graph.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

vertex *create_vertex(int index) {
  vertex *x = malloc(sizeof(vertex));
  x->index = index;
  x->weight = 0;
  x->next = NULL;
  return x;
}

void insert_edge(vertex graph[], int u, int v) {
  vertex *x = create_vertex(v);
  x->next = graph[u].next;
  graph[u].next = x;
}

void insert_weighted_edge(vertex graph[], int u, int v, int w){
  vertex *x = create_vertex(v);
  x->weight = w;
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

vertex *transpose(vertex *graph, int n) {
  vertex *t_graph = malloc(sizeof(vertex) * n);
  for (int i = 0; i < n; i++) {
    vertex *p = graph[i].next;
    while (p) {
      insert_edge(t_graph, p->index, i);
      p = p->next;
    }
  }
  return t_graph;
}

int is_edge(vertex *graph, int u, int v) {
  vertex *p = &graph[u];
  while (p) {
    if (p->index == v) return 1;
    p = p->next;
  }
  return 0;
}

void dfs_visit(vertex *graph, int u, char *color, int n, int indent) {
  color[u] = 'G';
  for (int i = 0; i < indent; i++)
    printf("    |");
  printf("----");
  printf("%d\n", u);
  for (int i = 0; i < n; i++)
    if (is_edge(graph, u, i) && color[i] == 'W') dfs_visit(graph, i, color, n, indent + 1);
  color[u] = 'B';
}

void pretty_print_dfs(vertex *graph, int n) {
  char color[n];
  for (int i = 0; i < n; i++)
    color[i] = 'W';
  for (int i = 0; i < n; i++)
    if (color[i] == 'W') dfs_visit(graph, i, color, n, 0);
}
