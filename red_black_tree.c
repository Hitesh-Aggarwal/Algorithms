#include <stdio.h>
#include <stdlib.h>

#define N 10

typedef struct node {
  int key;
  struct node *left;
  struct node *right;
  struct node *parent;
  char color;
} node;

void inorder(node *root, node *nil) {
  if (root != nil) {
    inorder(root->left, nil);
    printf("%d%c ", root->key, root->color);
    inorder(root->right, nil);
  }
}

void preorder(node *root, node *nil) {
  if (root != nil) {
    printf("%d%c ", root->key, root->color);
    preorder(root->left, nil);
    preorder(root->right, nil);
  }
}

node *tree_search(node *root, int k, node *nil) {
  while (root != nil && k != root->key) {
    if (k < root->key)
      root = root->left;
    else
      root = root->right;
  }
  return root;
}

node *tree_minimum(node *root, node *nil) {
  while (root->left != nil)
    root = root->left;
  return root;
}

node *tree_maximum(node *root, node *nil) {
  while (root->right != nil)
    root = root->right;
  return root;
}

node *tree_successor(node *x, node *nil) {
  if (x->right != nil) return tree_minimum(x->right, nil);
  node *y = x->parent;
  while (y != nil && x == y->right) {
    x = y;
    y = x->parent;
  }
  return y;
}

node *tree_predecessor(node *x, node *nil) {
  if (x->left != nil) return tree_maximum(x->left, nil);
  node *y = x->parent;
  while (y != nil && x == y->left) {
    x = y;
    y = x->parent;
  }
  return y;
}

node *left_rotate(node *root, node *x, node *nil) {
  node *y = x->right;
  x->right = y->left;
  if (y->left != nil) y->left->parent = x;
  y->parent = x->parent;
  if (x->parent == nil)
    root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->left = x;
  x->parent = y;
  return root;
}

node *right_rotate(node *root, node *x, node *nil) {
  node *y = x->left;
  x->left = y->right;
  if (y->right != nil) y->right->parent = x;
  y->parent = x->parent;
  if (x->parent == nil)
    root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->right = x;
  x->parent = y;
  return root;
}

node *rb_insert_fixup(node *root, node *z, node *nil) {
  while (z->parent->color == 'R') {
    if (z->parent == z->parent->parent->left) {
      node *y = z->parent->parent->right;
      if (y->color == 'R') {
        z->parent->color = 'B';
        y->color = 'B';
        z->parent->parent->color = 'R';
        z = z->parent->parent;
      } else {
        if (z == z->parent->right) {
          z = z->parent;
          root = left_rotate(root, z, nil);
        }
        z->parent->color = 'B';
        z->parent->parent->color = 'R';
        root = right_rotate(root, z->parent->parent, nil);
      }
    } else {
      node *y = z->parent->parent->left;
      if (y->color == 'R') {
        z->parent->color = 'B';
        y->color = 'B';
        z->parent->parent->color = 'R';
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          root = right_rotate(root, z, nil);
        }
        z->parent->color = 'B';
        z->parent->parent->color = 'R';
        root = left_rotate(root, z->parent->parent, nil);
      }
    }
  }
  root->color = 'B';
  return root;
}

node *rb_insert(node *root, node *z, node *nil) {
  node *y = nil;
  node *x = root;
  while (x != nil) {
    y = x;
    if (z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  z->parent = y;
  if (y == nil)
    root = z;
  else if (z->key < y->key)
    y->left = z;
  else
    y->right = z;
  z->left = nil;
  z->right = nil;
  z->color = 'R';
  root = rb_insert_fixup(root, z, nil);
  return root;
}

node *rb_transplant(node *root, node *u, node *v, node *nil) {
  if (u->parent == nil)
    root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  v->parent = u->parent;
  return root;
}

node *rb_delete_fixup(node *root, node *x, node *nil) {
  node *w = nil;
  while (x != root && x->color == 'B') {
    if (x == x->parent->left) {
      w = x->parent->right;
      if (w->color == 'R') {
        w->color = 'B';
        x->parent->color = 'R';
        root = left_rotate(root, x->parent, nil);
      }
      if (w->left->color == 'B' && w->right->color == 'B') {
        w->color = 'R';
        x = x->parent;
      } else {
        if (w->right->color == 'B') {
          w->left->color = 'B';
          w->color = 'R';
          root = right_rotate(root, w, nil);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = 'B';
        w->right->color = 'B';
        root = left_rotate(root, x->parent, nil);
        x = root;
      }
    } else {
      w = x->parent->left;
      if (w->color == 'R') {
        w->color = 'B';
        x->parent->color = 'R';
        root = right_rotate(root, x->parent, nil);
      }
      if (w->right->color == 'B' && w->left->color == 'B') {
        w->color = 'R';
        x = x->parent;
      } else {
        if (w->left->color == 'B') {
          w->right->color = 'B';
          w->color = 'R';
          root = left_rotate(root, w, nil);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = 'B';
        w->left->color = 'B';
        root = right_rotate(root, x->parent, nil);
        x = root;
      }
    }
  }
  return root;
}

node *rb_delete(node *root, node *z, node *nil) {
  node *y = z;
  node *x = nil;
  char y_orig_color = y->color;
  if (z->left == nil) {
    x = z->right;
    root = rb_transplant(root, z, z->right, nil);
  } else if (z->right == nil) {
    x = z->left;
    root = rb_transplant(root, z, z->left, nil);
  } else {
    y = tree_minimum(z->right, nil);
    y_orig_color = y->color;
    x = y->right;
    if (y->parent == z)
      x->parent = y;
    else {
      root = rb_transplant(root, y, y->right, nil);
      y->right = z->right;
      y->right->parent = y;
    }
    root = rb_transplant(root, z, y, nil);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  if (y_orig_color == 'B') root = rb_delete_fixup(root, x, nil);
  return root;
}

node *build_rb_tree(int arr[], int n, node *nil) {
  node *root = nil;
  while (n) {
    node *x = malloc(sizeof(node));
    x->key = arr[n - 1];
    root = rb_insert(root, x, nil);
    n = n - 1;
  }
  return root;
}

int main(int argc, char *argv[]) {
  int A[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  node *nil = malloc(sizeof(node));
  nil->color = 'B';
  node *root = build_rb_tree(A, N, nil);
  inorder(root, nil);
  printf("\n");
  printf("Root: %d\n", root->key);
  root = rb_delete(root, tree_search(root, 10, nil), nil);
  inorder(root, nil);
  printf("\n");
  printf("Root: %d\n", root->key);
  return 0;
}
