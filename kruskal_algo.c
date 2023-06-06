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

void kruskal(int graph[N][N]) {
  Node *node_list[N];
  for (int i = 0; i < N; i++) {
    node_list[i] = create_node(i);
    make_set(node_list[i]);
  }
  int u, v;
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
    printf("Edge chosen: %d --- %d\n", u, v);
  }
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
