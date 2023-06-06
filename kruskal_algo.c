#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define N 9

typedef struct Node {
  int key;
  int rank;
  struct Node *parent;
} Node;

Node *create_node(int key) {
  Node *x = malloc(sizeof(Node));
  x->key = key;
  x->parent = NULL;
  return x;
}

void make_set(Node *x) {
  x->parent = x;
  x->rank = 0;
}

Node *find_set(Node *x) {
  if (x != x->parent) x->parent = find_set(x->parent);
  return x->parent;
}

void link(Node *x, Node *y) {
  if (x->rank > y->rank)
    y->parent = x;
  else { x->parent = y; }
  if (x->rank == y->rank) y->rank = y->rank + 1;
}

#define Union(x, y) link(find_set(x), find_set(y))

void pretty_DFS_Visit(int graph[N][N], int u, char color[N], int indent) {
  color[u] = 'G';
  for (int i = 0; i < indent; i++)
    printf("    |");
  printf("----");
  printf("%d\n", u);
  for (int i = 0; i < N; i++) {
    if (graph[u][i] == 1 && color[i] == 'W') { pretty_DFS_Visit(graph, i, color, indent + 1); }
  }
  color[u] = 'B';
}

void pretty_dfs(int graph[N][N]) {
  char color[N];
  for (int i = 0; i < N; i++)
    color[i] = 'W';
  for (int i = 0; i < N; i++) {
    if (color[i] == 'W') pretty_DFS_Visit(graph, i, color, 0);
  }
}

void kruskal(int graph[N][N]) {
  int final_graph[N][N];
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      final_graph[i][j] = 0;

  Node *node_list[N];
  for (int i = 0; i < N; i++) {
    node_list[i] = create_node(i);
    make_set(node_list[i]);
  }
  int u = 0, v = 1;
  int min;
  int edge_count = 0;
  while (edge_count < N - 1) {
    min = INT_MAX;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (find_set(node_list[i]) != find_set(node_list[j]) && graph[i][j] < min) {
          min = graph[i][j];
          u = i;
          v = j;
        }
      }
    }
    Union(node_list[u], node_list[v]);
    edge_count = edge_count + 1;
    final_graph[u][v] = 1;
    final_graph[v][u] = 1;
    printf("Edge Selected: %d --- %d\n", u, v);
  }
  printf("\nFinal Tree:\n");
  pretty_dfs(final_graph);
  for(int i=0; i<N; i++)
    free(node_list[i]);
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
