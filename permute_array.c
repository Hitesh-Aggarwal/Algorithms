#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10

void randomize_array(int A[], int n) {
  for (int i = 0; i < n; i++) {
    int temp_index = (rand() % (n - i)) + i;
    int temp = A[i];
    A[i] = A[temp_index];
    A[temp_index] = temp;
  }
}

int main(int argc, char *argv[]) {
  time_t t;
  srand((unsigned)time(&t));
  int A[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  randomize_array(A, N);
  for (int i = 0; i < N; i++)
    printf("%d ", A[i]);
  printf("\n");
  return 0;
}
