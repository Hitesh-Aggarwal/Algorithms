#include <stdio.h>
#include <stdlib.h>

#define N 16

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

int main(int argc, char *argv[]) {
  Node *node_list[N];
  for (int i = 0; i < N; i++)
    node_list[i] = create_node(i + 1);

  for(int i=0; i<N; i++)
    make_set(node_list[i]);

  for(int i=0; i<N-1; i+=2)
    Union(node_list[i], node_list[i+1]);
  for(int i=0; i<N-3; i+=4)
    Union(node_list[i],node_list[i+2]);
  Union(node_list[0], node_list[4]);
  Union(node_list[10], node_list[12]);
  Union(node_list[0], node_list[9]);

  printf("%d\n", find_set(node_list[1])->key);
  printf("%d\n", find_set(node_list[8])->key);
  return 0;
}
