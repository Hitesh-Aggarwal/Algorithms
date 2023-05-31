#include <stdio.h>
#include <stdlib.h>

#define N 16

struct Set;

typedef struct Member {
  int key;
  struct Member *next;
  struct Set *set;
} Member;

typedef struct Set {
  struct Member *head;
  struct Member *tail;
  int items;
} Set;

Member *create_member(int key) {
  Member *x = malloc(sizeof(Member));
  x->key = key;
  x->next = NULL;
  x->set = NULL;
  return x;
}

void make_set(Member *x) {
  x->set = malloc(sizeof(Set));
  x->set->head = x;
  x->set->tail = x;
  x->set->items = 1;
}

Member *find_set(Member *x) {
  if (x->set)
    return x->set->head;
  else
    return NULL;
}

void Union(Member *x, Member *y) {
  if (x->set == NULL || y->set == NULL) return;
  Member *s = y; // s means smaller set.
  Member *l = x; // l means larger set.
  if (x->set->items < s->set->items) {
    s = x;
    l = y;
  }
  Set *s_set = s->set;
  l->set->tail->next = s_set->head;
  Member *ptr = s_set->head;
  while (ptr->next != NULL) {
    ptr->set = l->set;
    ptr = ptr->next;
  }
  ptr->set = l->set;
  l->set->tail = ptr;
  l->set->items = l->set->items + s_set->items;
  free(s_set);
}

int main(int argc, char *argv[]) {
  Member *members[N];
  for (int i = 0; i < N; i++)
    members[i] = create_member(i+1);
  for(int i=0; i<N; i++)
    make_set(members[i]);

  for(int i=0; i<N-1; i+=2)
    Union(members[i], members[i+1]);
  for(int i=0; i<N-3; i+=4)
    Union(members[i],members[i+2]);
  Union(members[0], members[4]);
  Union(members[10], members[12]);
  Union(members[0], members[9]);

  printf("%d\n", find_set(members[1])->key);
  printf("%d\n", find_set(members[8])->key);
  return 0;
}
