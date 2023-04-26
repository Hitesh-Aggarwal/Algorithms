#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

void random_search(int A[], int n, int x) {
  int counter = 0;
  int B[N] = {0};
  int ct = 0;
  int flag = 1;
  int found = 0;
  while (flag) {
    counter++;
    int a = rand() % N;
    if (A[a] == x) {
      flag = 0;
      found = 1;
    }
    if (B[a] == 0) {
      B[a] = 1;
      ct++;
    }
    if (ct >= n) flag = 0;
  }
  if (found)
    printf("Found in %d iterations\n", counter);
  else
    printf("Not found\n");
}

int main(int argc, char *argv[]) {
  int A[N] = {5, 7, 6, 8, 10, 1, 4, 3, 9, 2};
  time_t t;
  srand(time(&t));
  random_search(A, N, 8);
  return 0;
}
