#include "disjoint_sets.h"
#include <stdlib.h>

int *parent;
int *rank;

void initialize_sets(int cap) {
  parent = malloc(sizeof(int) * cap);
  rank = malloc(sizeof(int) * cap);
}

void make_set(int x) {
  parent[x] = x;
  rank[x] = 0;
}

int find_set(int x) {
  if (parent[x] != x) parent[x] = find_set(parent[x]);
  return parent[x];
}

void link(int x, int y) {
  if (rank[x] > rank[y])
    parent[y] = x;
  else
    parent[x] = y;
  if (rank[x] == rank[y]) rank[y] = rank[y] + 1;
}

void Union(int x, int y) { link(find_set(x), find_set(y)); }

void destroy_sets() {
  free(parent);
  free(rank);
}
