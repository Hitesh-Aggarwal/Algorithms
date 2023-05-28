#include <stdio.h>
#include <stdlib.h>

#define T 2
#define N 21

typedef struct B_tree {
  int key[2 * T - 1];
  struct B_tree *child[2 * T];
  int n;
  int leaf;
} B_tree;

B_tree *B_tree_create() {
  B_tree *root = malloc(sizeof(B_tree));
  root->leaf = 1;
  root->n = 0;
  return root;
}

void B_tree_split_child(B_tree *x, int i) {
  B_tree *z = malloc(sizeof(B_tree));
  B_tree *y = x->child[i];
  z->leaf = y->leaf;
  z->n = T - 1;
  for (int j = 0; j < T - 1; j++)
    z->key[j] = y->key[j + T];
  if (y->leaf == 0) {
    for (int j = 0; j < T; j++)
      z->child[j] = y->child[j + T];
  }
  y->n = T - 1;
  for (int j = x->n; j >= i + 1; j--)
    x->child[j + 1] = x->child[j];
  x->child[i + 1] = z;
  for (int j = x->n - 1; j >= i; j--)
    x->key[j + 1] = x->key[j];

  x->key[i] = y->key[T - 1];
  x->n = x->n + 1;
}

void B_tree_insert_non_full(B_tree *x, int k) {
  int i = x->n - 1;
  if (x->leaf) {
    while (i >= 0 && k < x->key[i]) {
      x->key[i + 1] = x->key[i];
      i = i - 1;
    }
    x->key[i + 1] = k;
    x->n = x->n + 1;
  } else {
    while (i >= 0 && k < x->key[i])
      i = i - 1;
    i = i + 1;
    if (x->child[i]->n == 2 * T - 1) {
      B_tree_split_child(x, i);
      if (k > x->key[i]) i = i + 1;
    }
    B_tree_insert_non_full(x->child[i], k);
  }
}

B_tree *B_tree_insert(B_tree *root, int k) {
  B_tree *r = root;
  if (root->n == 2 * T - 1) {
    B_tree *s = malloc(sizeof(B_tree));
    root = s;
    s->leaf = 0;
    s->n = 0;
    s->child[0] = r;
    B_tree_split_child(s, 0);
    B_tree_insert_non_full(s, k);
  } else
    B_tree_insert_non_full(r, k);
  return root;
}

void B_tree_search(B_tree *root, int k, B_tree **x, int *i) {
  int j = 0;
  while (j < root->n && k > root->key[j])
    j = j + 1;
  if (j < root->n && k == root->key[j]) {
    *x = root;
    *i = j;
    return;
  } else if (root->leaf) {
    *x = NULL;
    *i = -1;
    return;
  } else
    B_tree_search(root->child[j], k, x, i);
}

int B_tree_minimum(B_tree *root) {
  if (root->leaf)
    return root->key[0];
  else
    return B_tree_minimum(root->child[0]);
}

int B_tree_maximum(B_tree *root) {
  if (root->leaf)
    return root->key[root->n - 1];
  else
    return B_tree_maximum(root->child[root->n]);
}

B_tree *B_tree_find_parent(B_tree *root, int k) {
  B_tree *parent = NULL;
  B_tree *c = root;
  while (c) {
    int i = 0;
    while (i < c->n && k > c->key[i])
      i++;
    if (i < c->n && k == c->key[i]) return parent;
    parent = c;
    c = parent->child[i];
  }
  return NULL;
}

int B_tree_predecessor(B_tree *root, int k) {
  B_tree *x;
  int i;
  B_tree_search(root, k, &x, &i);
  if (!(x->leaf)) {
    return B_tree_maximum(x->child[i]);
  } else {
    if (i > 0)
      return x->key[i - 1];
    else {
      B_tree *y;
      while (1) {
        y = B_tree_find_parent(root, x->key[0]);
        if (y == NULL) return -1;
        int j = 0;
        while (y->child[j] != x)
          j = j + 1;
        if (j == 0)
          x = y;
        else
          return y->key[j - 1];
      }
    }
  }
}

void B_tree_traverse(B_tree *x) {
  if (x->leaf) {
    printf("\nNew Node: ");
    for (int i = 0; i < x->n; i++)
      printf("%c ", x->key[i]);
  } else {
    printf("\nNew Node: ");
    for (int i = 0; i < x->n; i++)
      printf("%c ", x->key[i]);
    for (int i = 0; i <= x->n; i++)
      B_tree_traverse(x->child[i]);
  }
}

int main(int argc, char *argv[]) {
  B_tree *root = B_tree_create();
  char arr[N] = {'F', 'S', 'Q', 'K', 'C', 'L', 'H', 'T', 'V', 'W', 'M',
                 'R', 'N', 'P', 'A', 'B', 'X', 'Y', 'D', 'Z', 'E'};
  for (int i = 0; i < N; i++)
    root = B_tree_insert(root, arr[i]);

  // printf("%c\n", B_tree_minimum(root));
  // printf("%c\n", B_tree_maximum(root));
  // printf("%c\n", B_tree_predecessor(root, 'V'));
  B_tree_traverse(root);
  return 0;
}
