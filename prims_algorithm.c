#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define N 9
#define parent(i) ((i + 1) / 2 - 1)
#define left(i) ((2 * (i + 1) - 1))
#define right(i) (2 * (i + 1))
#define is_empty(pq) (pq->heap_size == 0)

typedef struct node {
  int vertex;
  int key;
  int predecessor;
} node;

typedef struct PQ {
  node **elements;
  int heap_size;
} PQ;

PQ *create_heap() {
  PQ *pq = malloc(sizeof(PQ));
  pq->elements = malloc(sizeof(node *) * N);
  pq->heap_size = 0;
  return pq;
}

void MinHeapify(PQ *pq, int i) {
  int l = left(i);
  int r = right(i);
  int smallest = l;
  node *temp;
  if (l < pq->heap_size && pq->elements[l]->key < pq->elements[i]->key)
    smallest = l;
  else
    smallest = i;
  if (r < pq->heap_size && pq->elements[r]->key < pq->elements[smallest]->key) smallest = r;
  if (smallest != i) {
    temp = pq->elements[i];
    pq->elements[i] = pq->elements[smallest];
    pq->elements[smallest] = temp;
    MinHeapify(pq, smallest);
  }
}

node *heap_extract_min(PQ *pq) {
  if (pq->heap_size < 1) {
    printf("Heap underflow");
    return NULL;
  }
  node *min = pq->elements[0];
  pq->elements[0] = pq->elements[pq->heap_size - 1];
  pq->elements[pq->heap_size - 1] = NULL;
  pq->heap_size = pq->heap_size - 1;
  MinHeapify(pq, 0);
  return min;
}

void Heap_decrease_key(PQ *pq, int i, int k) {
  if (i >= pq->heap_size) return;
  if (k > pq->elements[i]->key) {
    printf("new key larger than current key");
    return;
  }
  pq->elements[i]->key = k;
  node *temp = pq->elements[i];
  while (i > 0 && pq->elements[parent(i)]->key > temp->key) {
    pq->elements[i] = pq->elements[parent(i)];
    i = parent(i);
  }
  pq->elements[i] = temp;
}

int is_present(PQ *pq, node *v) {
  int flag = 0;
  for (int i = 0; i < pq->heap_size; i++)
    if (pq->elements[i] == v) {
      flag = 1;
      break;
    }
  return flag;
}

void min_heap_insert(PQ *pq, node *v) {
  if (pq->heap_size >= N) {
    printf("Heap Overflow");
    return;
  }
  int k = v->key;
  v->key = INT_MAX;
  pq->elements[pq->heap_size] = v;
  pq->heap_size = pq->heap_size + 1;
  Heap_decrease_key(pq, pq->heap_size - 1, k);
}

void Change_key(PQ *pq, node *v, int k) {
  for (int i = 0; i < pq->heap_size; i++) {
    if (pq->elements[i] == v) {
      Heap_decrease_key(pq, i, k);
      break;
    }
  }
}

void print_heap(PQ *pq) {
  printf("\n");
  for (int i = 0; i < pq->heap_size; i++)
    printf("Vertex = %d    Key = %d\n", pq->elements[i]->vertex, pq->elements[i]->key);
}

void MST_prim(int graph[N][N]) {
  PQ *pq = create_heap();
  node vertices[N];
  for (int i = 0; i < N; i++) {
    vertices[i].key = INT_MAX;
    vertices[i].predecessor = -1;
    vertices[i].vertex = i;
  }

  vertices[0].key = 0;
  for (int i = 0; i < N; i++)
    min_heap_insert(pq, &vertices[i]);

  while (!is_empty(pq)) {
    node *u = heap_extract_min(pq);
    for (int i = 0; i < N; i++) {
      if (graph[u->vertex][vertices[i].vertex] != INT_MAX) {
        if (is_present(pq, &vertices[i]) && graph[u->vertex][i] < vertices[i].key) {
          vertices[i].predecessor = u->vertex;
          Change_key(pq, &vertices[i], graph[u->vertex][i]);
        }
      }
    }
    if (u->vertex > 0) { printf("\nEdge Selected: %d ---- %d", u->predecessor, u->vertex); }
  }
  free(pq);
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

  MST_prim(graph);
  return EXIT_SUCCESS;
}
