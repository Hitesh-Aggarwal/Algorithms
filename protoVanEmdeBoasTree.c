#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* U is of the form 2^(2k) */
#define U 16

#define sqt(x) ((int)sqrt(x))

/* high(x) gives number of x's cluster
   high(x) = x / sqrt(U)
   high(x) gives the most significant lg(U)/2 bits of x.
*/
#define high(x, u) (x / sqt(u))

/* low(x) gives x's position within its cluster
   low(x) = x % sqrt(U)
   low(x) gives least significant lg(U)/2 bits of x.
*/
#define low(x, u) (x % sqt(u))

/* index(x,y) builds the index given cluster number x
   and position y within the cluster.

   ==> we have this identity:
   x = index(high(x), low(x))
*/
#define index(x, y, u) (sqt(u) * x + y)

/*
   The Proto_vEB(u) structure
   ==> u is the universe size.

   if u >= 4 then
   ==> summary points to Proto_vEB(sqrt(u)) structure
   ==> cluster is an array[0 .. sqrt(u)-1], each element
        points to proto_vEB(sqrt(u)) structure.

  if u == 2 then
   ==> summary is NULL
   ==> cluster is an array[0..1].
      If element i is not present, cluster[i] = 0.
      If element i is present, cluster[i] points to
      a dummy proto_vEB(0) node, which has both summary
      and cluster set to NULL.

      i.e, 0 is represented by NULL and 1 is represented by
      pointer to dummy node (basically not NULL)
*/
typedef struct Proto_vEB {
  int u;
  struct Proto_vEB *summary;
  struct Proto_vEB **cluster;
} Proto_vEB;

/* This is the dummy node */
Proto_vEB dummy_node = {0, NULL, NULL};
#define dummy (&dummy_node)

/* creates the proto_vEB structure */
Proto_vEB *create_proto_vEB(int u) {
  Proto_vEB *x = malloc(sizeof(Proto_vEB));
  x->u = u;
  if (u == 2) {
    x->summary = NULL;
    x->cluster = malloc(sizeof(Proto_vEB *) * u);
    for (int i = 0; i < u; i++)
      x->cluster[i] = NULL;
  } else {
    x->summary = create_proto_vEB(sqt(u));
    x->cluster = malloc(sizeof(Proto_vEB *) * sqt(u));
    for (int i = 0; i < sqt(u); i++)
      x->cluster[i] = create_proto_vEB(sqt(u));
  }
  return x;
}

/* Returns true if x is member of the proto_vEB */
int Proto_vEB_member(Proto_vEB *V, int x) {
  if (x > V->u) return 0;
  if (V->u == 2)
    return (V->cluster[x] == NULL) ? 0 : 1;
  else
    return Proto_vEB_member(V->cluster[high(x, V->u)], low(x, V->u));
  return 0;
}

/* Returns the minimum value in the set */
int Proto_vEB_minimum(Proto_vEB *V) {
  // base case
  if (V->u == 2) {
    if (V->cluster[0] != NULL)
      return 0;
    else if (V->cluster[1] != NULL)
      return 1;
    else
      return INT_MIN;
  }
  // recursive case.
  else {
    // find the next cluster which has a value.
    int min_cluster = Proto_vEB_minimum(V->summary);
    // if no such cluster, return failure
    if (min_cluster == INT_MIN) return INT_MIN;
    // else find minimum in that cluster
    else {
      int offset = Proto_vEB_minimum(V->cluster[min_cluster]);
      return index(min_cluster, offset, V->u);
    }
  }
}

int Proto_vEB_Successor(Proto_vEB *V, int x) {
  // base case.
  if (V->u == 2) {
    if (x == 0 && V->cluster[1] != NULL)
      return 1;
    else
      return INT_MIN;
  } else {
    // find x's successor in the same cluster.
    int offset = Proto_vEB_Successor(V->cluster[high(x, V->u)], low(x, V->u));
    if (offset != INT_MIN) return index(high(x, V->u), offset, V->u);
    // if not found in same cluster
    else {
      // find the successor cluster of current cluster using summaries.
      int succ_cluster = Proto_vEB_Successor(V->summary, high(x, V->u));
      // if no such cluster found return failure.
      if (succ_cluster == INT_MIN) return INT_MIN;
      // else find the minimum value in that cluster and return it.
      else {
        offset = Proto_vEB_minimum(V->cluster[succ_cluster]);
        return index(succ_cluster, offset, V->u);
      }
    }
  }
}

/* Inserts element x into proto_vEB */
void Proto_vEB_insert(Proto_vEB *V, int x) {
  if (V->u == 2)
    V->cluster[x] = dummy;
  else {
    Proto_vEB_insert(V->cluster[high(x, V->u)], low(x, V->u));
    Proto_vEB_insert(V->summary, high(x, V->u));
  }
}

void Destroy_Proto_vEB(Proto_vEB *V) {
  if (V->u == 2) {
    V->cluster[0] = NULL;
    V->cluster[1] = NULL;
    free(V->cluster);
    free(V);
  } else {
    Destroy_Proto_vEB(V->summary);
    for (int i = 0; i < sqt(V->u); i++) {
      Destroy_Proto_vEB(V->cluster[i]);
    }
  }
}

int main(int argc, char *argv[]) {
  int arr[] = {2, 3, 4, 5, 7, 14, 15};
  int n = sizeof(arr) / sizeof(int);
  Proto_vEB *V = create_proto_vEB(U);
  for (int i = 0; i < n; i++)
    Proto_vEB_insert(V, arr[i]);
  printf("%d\n", Proto_vEB_member(V, 4));
  printf("%d\n", Proto_vEB_minimum(V));
  printf("%d\n", Proto_vEB_Successor(V, 5));
  Destroy_Proto_vEB(V);
  V = NULL;
  return EXIT_SUCCESS;
}
