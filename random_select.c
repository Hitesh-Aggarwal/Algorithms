#include <stdio.h>
#include <stdlib.h>
#define N 10

int partition(int *A, int p, int r) {
  long x = A[r];
  long temp;
  int i = p - 1;
  for (int j = p; j <= r - 1; j++) {
    if (A[j] <= x) {
      i++;
      temp = A[i];
      A[i] = A[j];
      A[j] = temp;
    }
  }
  temp = A[i + 1];
  A[i + 1] = A[r];
  A[r] = temp;
  return i + 1;
}

int randomPartition(int *A, int p, int r) {
  int i = (rand() % (r - p + 1)) + p;
  long temp = A[i];
  A[i] = A[r];
  A[r] = temp;
  return partition(A, p, r);
}

int randomized_select(int *A, int p, int r, int i) {
  if (p == r)
    return A[p];
  int q = randomPartition(A, p, r);
  int k = q - p + 1;
  if (i == k)
    return A[q];
  else if (i < k)
    return randomized_select(A, p, q - 1, i);
  else
    return randomized_select(A, q + 1, r, i - k);
}

int main(int argc, char *argv[]) {
  int A[N] = {24, 15, 903, -23, 52, -523, 32, 54, -24, 12};
  printf("%d\n", randomized_select(A,0,N-1,9));
  for(int i=0; i<N; i++)
    printf("%d ",A[i]);
  printf("\n");
  return 0;
}
