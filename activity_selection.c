#include <stdio.h>

#define N 12

void recursive_activity_selector(int *startTime, int *finishTime, int k, int n) {
  int m = k + 1;
  while (m < n && startTime[m] <= finishTime[k])
    m = m + 1;
  if (m < n) {
    printf("%d ", m);
    recursive_activity_selector(startTime, finishTime, m, n);
  }
}

void greedy_activity_selector(int *startTime, int *finishTime, int n) {
  int k = 0;
  for (int m = 1; m < n; m++) {
    if (startTime[m] >= finishTime[k]) {
      printf("%d ", m);
      k = m;
    }
  }
}

void print_dp_activities(int *S, int *C, int i, int j, int n) {
  if (C[i * n + j] > 0) {
    int k = S[i * n + j];
    print_dp_activities(S, C, i, k, n);
    printf("%d ", k);
    print_dp_activities(S, C, k, j, n);
  }
}

void dp_activity_selector(int *startTime, int *finishTime, int n, int *C, int *S) {
  for (int i = 0; i < n*n; i++) {
    C[i] = 0;
    S[i] = 0;
  }

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      // find any activity k that starts after i finishes and finish before j starts.
      for (int k = i + 1; k < j; k++) {
        if ((startTime[k] >= finishTime[i] && finishTime[k] <= startTime[j]) &&
            (C[i * n + k] + C[k * n + j] + 1 > C[i * n + j])) {
          C[i * n + j] = C[i * n + k] + C[k * n + j] + 1;
          S[i * n + j] = k;
        }
      }
    }
  }
  print_dp_activities(S, C, 0, n - 1, n);
}

int main(int argc, char *argv[]) {
  int startTime[N + 1] = {0, 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12, 20};
  int finishTime[N + 1] = {0, 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16, 30};
  int C[N + 1][N + 1], S[N + 1][N + 1];
  printf("DP Algo: ");
  dp_activity_selector(startTime, finishTime, N + 1, (int *)C, (int *)S);
  printf("\n");

  printf("Greedy Algo (recursive): ");
  recursive_activity_selector(startTime, finishTime, 0, N);
  printf("\n");
  printf("Greedy Algo (iterative): ");
  greedy_activity_selector(startTime, finishTime, N);
  printf("\n");

  return 0;
}
