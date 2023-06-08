#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "queue.h"

#define N 8

void BFS(vertex graph[], int n, int s) {
  char color[n];
  int dist[n];
  int predecessor[n];
  Queue *Q = make_queue(N);
  // make an array to store pointers since queue stores void * pointers.
  int *pointer[N];
  for(int i=0; i<N; i++){
    pointer[i] = malloc(sizeof(int));
    *pointer[i] = i;
  }

  for (int i = 0; i < n; i++) {
    if (i == s) continue;
    color[i] = 'W';
    dist[i] = INT_MAX;
    predecessor[i] = -1;
  }
  color[s] = 'G';
  dist[s] = 0;
  predecessor[s] = -1;
  enqueue(Q, pointer[s]);
  printf("Node\tPredecessor\tDistanceFromSource\n");
  while (!is_empty(Q)) {
    int *u = dequeue(Q);
    vertex *p = graph[*u].next;
    while (p != NULL) {
      if (color[p->index] == 'W') {
        color[p->index] = 'G';
        dist[p->index] = dist[*u] + 1;
        predecessor[p->index] = *u;
        enqueue(Q, pointer[p->index]);
      }
      p = p->next;
    }
    color[*u] = 'B';
    printf("%d\t%d\t\t%d\n", *u, predecessor[*u], dist[*u]);
  }
  free_queue(Q);
  for(int i=0; i<N; i++)
    free(pointer[i]);
}

int main(int argc, char *argv[]) {
  vertex graph[N];
  for (int i = 0; i < N; i++) {
    graph[i].index = i;
    graph[i].next = NULL;
  }
  insert_edge(graph, 0, 1);
  insert_edge(graph, 0, 4);
  insert_edge(graph, 1, 0);
  insert_edge(graph, 1, 5);
  insert_edge(graph, 2, 3);
  insert_edge(graph, 2, 5);
  insert_edge(graph, 2, 6);
  insert_edge(graph, 3, 2);
  insert_edge(graph, 3, 6);
  insert_edge(graph, 3, 7);
  insert_edge(graph, 4, 0);
  insert_edge(graph, 5, 1);
  insert_edge(graph, 5, 2);
  insert_edge(graph, 5, 6);
  insert_edge(graph, 6, 7);
  insert_edge(graph, 6, 5);
  insert_edge(graph, 6, 2);
  insert_edge(graph, 6, 3);
  insert_edge(graph, 7, 3);
  insert_edge(graph, 7, 6);
  BFS(graph, N, 0);
  free_graph(graph, N);
  return EXIT_SUCCESS;
}
