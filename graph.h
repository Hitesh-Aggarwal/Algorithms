#ifndef GRAPH_H
#define GRAPH_H

typedef struct vertex {
  int index;
  struct vertex *next;
} vertex;

vertex *create_vertex(int index);
vertex *transpose(vertex* graph, int n);
void insert_edge(vertex graph[], int u, int v);
int is_edge(vertex *graph, int u, int v);
void free_graph(vertex graph[], int n);
void pretty_print_dfs(vertex *graph, int n);
#endif /* GRAPH_H */
