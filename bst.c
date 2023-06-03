#include <stdio.h>
#include <stdlib.h>

#define N 10

typedef struct node {
  int key;
  struct node *left;
  struct node *right;
  struct node *parent;
} node;

void pretty_print(node *root, int depth) {
  if (root) {
    for (int i = 0; i < depth; i++)
      printf("     ");
    printf("|----");
    printf("%d\n", root->key);
    pretty_print(root->left, depth + 1);
    pretty_print(root->right, depth + 1);
  }
}

void inorder(node *root) {
  if (root) {
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
  }
}

void preorder(node *root) {
  if (root) {
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
  }
}

void postorder(node *root) {
  if (root) {
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->key);
  }
}

node *tree_search(node *root, int k) {
  while (root && k != root->key) {
    if (k < root->key)
      root = root->left;
    else
      root = root->right;
  }
  return root;
}

node *tree_minimum(node *root) {
  while (root->left)
    root = root->left;
  return root;
}

node *tree_maximum(node *root) {
  while (root->right)
    root = root->right;
  return root;
}

node *tree_successor(node *x) {
  if (x->right) return tree_minimum(x->right);
  node *y = x->parent;
  while (y && x == y->right) {
    x = y;
    y = x->parent;
  }
  return y;
}

node *tree_predecessor(node *x) {
  if (x->left) return tree_maximum(x->left);
  node *y = x->parent;
  while (y && x == y->left) {
    x = y;
    y = x->parent;
  }
  return y;
}

node *tree_insert(node *root, node *x) {
  node *old_root = root;
  node *y = NULL;
  while (root) {
    y = root;
    if (x->key < root->key)
      root = root->left;
    else
      root = root->right;
  }
  x->parent = y;
  if (y == NULL)
    return x;
  else if (x->key < y->key)
    y->left = x;
  else
    y->right = x;
  return old_root;
}

node *transplant(node *root, node *u, node *v) {
  if (u->parent == NULL)
    root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  if (v != NULL) v->parent = u->parent;
  return root;
}

node *tree_delete(node *root, node *z) {
  if (z->left == NULL)
    root = transplant(root, z, z->right);
  else if (z->right == NULL)
    root = transplant(root, z, z->left);
  else {
    node *y = tree_minimum(z->right);
    if (y->parent != z) {
      root = transplant(root, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    root = transplant(root, z, y);
    y->left = z->left;
    y->left->parent = y;
  }
  return root;
}

node *build_random_bst(int arr[], int n) {
  node *root = NULL;
  while (n) {
    int i = (rand() % n);
    int temp = arr[i];
    arr[i] = arr[n - 1];
    arr[n - 1] = temp;
    node *x = malloc(sizeof(node));
    x->key = arr[n - 1];
    root = tree_insert(root, x);
    n = n - 1;
  }
  return root;
}

int main(int argc, char *argv[]) {
  int arr[N] = {81, 11, 91, 21, 31, 41, 71, 61, 51, 1};
  node *root = build_random_bst(arr, N);
  pretty_print(root, 0);
  printf("\n");

  root = tree_delete(root, tree_search(root, 1));
  pretty_print(root, 0);
  printf("\n");
  return 0;
}
