/* This is a circular linked list */
#include <limits.h>
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
  node *x = L->next;
  while (x != L && x->key != k)
    x = x->next;
  return x;
}

void list_insert(node *L, node *x) {
  x->next = L->next;
  L->next->prev = x;
  L->next = x;
  x->prev = L;
}

void list_delete(node *L, node *x) {
  x->prev->next = x->next;
  x->next->prev = x->prev;
}

void printList(node *L) {
  node *x = L->next;
  while (x != L) {
    printf("%d ", x->key);
    x = x->next;
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  node *head = create_node(INT_MIN); /* Sentinal Node */
  head->prev = head;
  head->next = head;
  list_insert(head, create_node(3));
  list_insert(head, create_node(8));
  list_insert(head, create_node(7));
  list_insert(head, create_node(1));
  list_insert(head, create_node(6));
  list_insert(head, create_node(0));
  printList(head);
  list_delete(head, head->next);
  printList(head);
  return EXIT_SUCCESS;
}
