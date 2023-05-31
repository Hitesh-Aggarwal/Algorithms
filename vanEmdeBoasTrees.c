#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define U 16

/*
   upper_sqrt(U) = 2^ceil(lg(U)/2)
   lower_sqrt(U) = 2^floor(lg(U)/2)

   U = upper_sqrt(U)*lower_sqrt(U)
*/
#define upper_sqrt(u) ((int)pow(2, (int)ceil(log2(u) / 2)))
#define lower_sqrt(u) ((int)pow(2, (int)(log2(u) / 2)))

/* high(x) gives number of x's cluster
   high(x) = x / lower_sqrt(U)
   high(x) gives the most significant ceil(lg(U)/2) bits of x.
*/
#define high(x, u) (x / lower_sqrt(u))

/* low(x) gives x's position within its cluster
   low(x) = x % lower_sqrt(U)
   low(x) gives least significant floor(lg(U)/2) bits of x.
*/
#define low(x, u) (x % lower_sqrt(u))

/* index(x,y) builds the index given cluster number x
   and position y within the cluster.

   ==> we have this identity:
   x = index(high(x), low(x))
*/
#define index(x, y, u) (lower_sqrt(u) * x + y)

/*
   The van Emde Boas tree, or vEB(u) structure:
   ==> u is the universe size.
   ==> min and max store minimum and maximum value in the tree.

   if u >= 4 then
   ==> summary points to vEB(upper_sqrt(u)) structure
   ==> cluster is an array[0 .. upper_sqrt(u)-1], each element
        points to vEB(lower_sqrt(u)) structure.
*/
typedef struct vEB_tree {
  int u;
  struct vEB_tree *summary;
  struct vEB_tree **cluster;
  int min;
  int max;
} vEB_tree;

/* Creates an empty vEB_tree */
vEB_tree *create_vEB(int u) {
  vEB_tree *x = malloc(sizeof(vEB_tree));
  x->u = u;
  if (u == 2) {
    x->summary = NULL;
    x->cluster = NULL;
    x->min = INT_MIN;
    x->max = INT_MIN;
  } else {
    x->summary = create_vEB(upper_sqrt(u));
    x->cluster = malloc(sizeof(vEB_tree) * upper_sqrt(u));
    for (int i = 0; i < upper_sqrt(u); i++) {
      x->cluster[i] = create_vEB(lower_sqrt(u));
    }
    x->max = INT_MIN;
    x->min = INT_MIN;
  }
  return x;
}

/* Returns the minimum element from tree */
#define vEB_tree_minimum(V) (V->min)

/* Returns the maximum element from tree */
#define vEB_tree_maximum(V) (V->max)

/* Checks whether x is in V */
int vEB_tree_member(vEB_tree *V, int x) {
  if (x == V->min || x == V->max)
    return 1;
  else if (V->u == 2)
    return 0;
  else
    return vEB_tree_member(V->cluster[high(x, V->u)], low(x, V->u));
}

/* Returns successor of x */
int vEB_tree_successor(vEB_tree *V, int x) {
  // base case...
  if (V->u == 2) {
    // in a two element set, if x is 0 and 1 is present, return 1
    if (x == 0 && V->max == 1) return 1;
    // else return failure
    else
      return INT_MIN;
  }
  // if x is less then minimum element, return the minimum element.
  else if (V->min != INT_MIN && x < V->min)
    return V->min;
  else {
    // max_low is maximum value in the x's own cluster.
    int max_low = vEB_tree_maximum(V->cluster[high(x, V->u)]);
    // if x is less than the max value, successor lies in its cluster.
    if (max_low != INT_MIN && low(x, V->u) < max_low) {
      int offset = vEB_tree_successor(V->cluster[high(x, V->u)], low(x, V->u));
      return index(high(x, V->u), offset, V->u);
    }
    // else the successor lies in some higher number cluster.
    else {
      // determines the next non-empty cluster.
      int succ_cluster = vEB_tree_successor(V->summary, high(x, V->u));
      if (succ_cluster == INT_MIN) return INT_MIN;
      // find minimum value in that cluster.
      else {
        int offset = vEB_tree_minimum(V->cluster[succ_cluster]);
        return index(succ_cluster, offset, V->u);
      }
    }
  }
}

/* Returns predecessor of x */
int vEB_tree_predecessor(vEB_tree *V, int x) {
  // base case...
  if (V->u == 2) {
    // in a two element set, if x is 1 and 0 is present, return 0
    if (x == 1 && V->min == 0) return 0;
    // else return failure
    else
      return INT_MIN;
  }
  // if x is greater then maximum element, return the maximum element.
  else if (V->max != INT_MIN && x > V->max)
    return V->max;
  else {
    // min_low is minimum value in the x's own cluster.
    int min_low = vEB_tree_minimum(V->cluster[high(x, V->u)]);
    // if x is greater than the min value, predecessor lies in its cluster.
    if (min_low != INT_MIN && low(x, V->u) > min_low) {
      int offset = vEB_tree_predecessor(V->cluster[high(x, V->u)], low(x, V->u));
      return index(high(x, V->u), offset, V->u);
    }
    // else the predecessor lies in some lower number cluster.
    else {
      // determines the previous non-empty cluster.
      int pred_cluster = vEB_tree_predecessor(V->summary, high(x, V->u));
      if (pred_cluster == INT_MIN) {
        // if x's predecessor is minimum value in vEB tree V,
        // then the successor lies in no cluster at all.
        if (V->min != INT_MIN && x > V->min)
          return V->min;
        else
          return INT_MIN;
      }
      // find maximum value in that cluster.
      else {
        int offset = vEB_tree_maximum(V->cluster[pred_cluster]);
        return index(pred_cluster, offset, V->u);
      }
    }
  }
}

/* Inserts a value into the vEB-tree */
void vEB_tree_insert(vEB_tree *V, int x) {
  // base case
  if (V->min == INT_MIN) {
    V->min = x;
    V->max = x;
  } else {
    // if x is less than V.min, swap V.min and x.
    if (x < V->min) {
      int temp = x;
      x = V->min;
      V->min = temp;
    }
    // Recursive case.
    if (V->u > 2) {
      // if x's cluster is empty
      if (vEB_tree_minimum(V->cluster[high(x, V->u)]) == INT_MIN) {
        // update the summary.
        vEB_tree_insert(V->summary, high(x, V->u));
        // insert x into that empty cluster.
        V->cluster[high(x, V->u)]->min = low(x, V->u);
        V->cluster[high(x, V->u)]->max = low(x, V->u);
      }
      // else insert x into it's cluster.
      // no need to update summary in this case as cluster is not empty.
      else
        vEB_tree_insert(V->cluster[high(x, V->u)], low(x, V->u));
    }
    if (x > V->max) V->max = x;
  }
}

/* Deletes a value from the vEB-tree */
void vEB_tree_delete(vEB_tree *V, int x) {
  // if V has only one element, just delete it by setting both min and max to null
  if (V->min == V->max) V->min = V->max = INT_MIN;
  // base case in which V contains two elements.
  else if (V->u == 2) {
    // just set V.max = V.min so that V contains only one element, that is not x.
    V->min = !x;
    V->max = V->min;
  }
  // Recursive case.
  else {
    if (x == V->min) { // if x = V.min
      // This line sets first_cluster to the number of cluster that contains the
      // lowest element other than V.min
      int first_cluster = vEB_tree_minimum(V->summary);
      // This line sets the value of x to that element.
      x = index(first_cluster, vEB_tree_minimum(V->cluster[first_cluster]), V->u);
      // update the V.min to that value, since this value will be
      // deleted from *its* cluster. (first_cluster)
      V->min = x;
    }
    // delete x from its cluster.
    vEB_tree_delete(V->cluster[high(x, V->u)], low(x, V->u));
    // test if that cluster is now empty.
    if (vEB_tree_minimum(V->cluster[high(x, V->u)]) == INT_MIN) {
      // if it is remove x's cluster number from summary.
      vEB_tree_delete(V->summary, high(x, V->u));
      // check is x is equal to V.max
      if (x == V->max) {
        // if it is, find the cluster number of maximum element that is not V.max
        int summary_max = vEB_tree_maximum(V->summary);
        if (summary_max == INT_MIN)
          // if no such cluster is found, only one element in v remains
          V->max = V->min;
        else
          V->max = index(summary_max, vEB_tree_maximum(V->cluster[summary_max]), V->u);
      }
    }
    // check is x is equal to V->max. If it is, find a new V.max from x's cluster.
    else if (x == V->max)
      V->max = index(high(x, V->u), vEB_tree_maximum(V->cluster[high(x, V->u)]), V->u);
  }
}

/* Frees the memory of tree */
void destroy_vEB(vEB_tree *V) {
  if (V->u == 2)
    free(V);
  else {
    destroy_vEB(V->summary);
    for (int i = 0; i < upper_sqrt(V->u); i++)
      destroy_vEB(V->cluster[i]);
    free(V);
  }
}

int main(int argc, char *argv[]) {
  int arr[] = {2, 3, 4, 5, 7, 14, 15};
  int n = sizeof(arr) / sizeof(int);
  vEB_tree *V = create_vEB(U);
  for (int i = 0; i < n; i++)
    vEB_tree_insert(V, arr[i]);
  for (int i = 0; i < 16; i++)
    printf("%d ", vEB_tree_member(V, i));
  printf("\n%d\n", vEB_tree_maximum(V));
  printf("%d\n", vEB_tree_minimum(V));
  printf("%d\n", vEB_tree_successor(V, 10));
  printf("%d\n", vEB_tree_predecessor(V, 10));
  vEB_tree_delete(V, 7);
  vEB_tree_delete(V, 2);
  for (int i = 0; i < 16; i++)
    printf("%d ", vEB_tree_member(V, i));
  destroy_vEB(V);
  printf("\n");
  return EXIT_SUCCESS;
}
