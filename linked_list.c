#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int key;
  struct node *prev;
  struct node *next;
} node;

node *create_node(int k) {
  node *x = malloc(sizeof(node));
  x->prev = x->next = NULL;
  x->key = k;
  return x;
}

node *list_search(node *L, int k) {
  node *x = L;
  while (x != NULL && x->key != k)
    x = x->next;
  return x;
}

node *list_insert(node *L, node *x) {
  x->next = L;
  if (L != NULL) L->prev = x;
  x->prev = NULL;
  L = x;
  return L;
}

node *list_delete(node *L, node *x) {
  if (x->prev != NULL)
    x->prev->next = x->next;
  else
    L = x->next;
  if (x->next != NULL) x->next->prev = x->prev;
  return L;
}

void printList(node *L) {
  while (L != NULL) {
    printf("%d ", L->key);
    L = L->next;
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  node *head = NULL;
  head = list_insert(head, create_node(3));
  head = list_insert(head, create_node(8));
  head = list_insert(head, create_node(7));
  head = list_insert(head, create_node(1));
  head = list_insert(head, create_node(6));
  head = list_insert(head, create_node(0));
  printList(head);
  head = list_delete(head, head);
  printList(head);
  return EXIT_SUCCESS;
}
