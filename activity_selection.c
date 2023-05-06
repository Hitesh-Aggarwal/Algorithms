#include <stdio.h>

#define N 12

typedef struct activity {
  int id;
  int startTime;
  int finishTime;
} activity;

void recursive_activity_selector(activity *list, int k, activity *selected, int *counter) {
  int m = k + 1;
  while (m < N && list[m].startTime < list[k].finishTime)
    m = m + 1;
  if (m < N) {
    selected[*counter] = list[m];
    *counter = *counter + 1;
    recursive_activity_selector(list, m, selected, counter);
  }
}

void greedy_activity_selector(activity *list, activity *selected, int *counter) {
  *counter = 0;
  selected[*counter] = list[1];
  *counter = 1;
  int k = 1;
  for (int m = 2; m < N; m++) {
    if (list[m].startTime >= list[k].finishTime) {
      selected[*counter] = list[m];
      (*counter)++;
      k = m;
    }
  }
}

void print_dp_activities(int *S, int i, int j, int n) {
  if (i < j) {
    if (S[i * n + j] > 0) {
      print_dp_activities(S, i, S[i * n + j], n);
      printf("%d ", S[i * n + j]);
      print_dp_activities(S, S[i * n + j], j, n);
    }
  }
}

void dp_activity_selector(activity *list, int n, int *C, int *S) {
  for (int i = 0; i < n * n; i++) {
    C[i] = 0;
    S[i] = 0;
  }

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      // find any activity k that starts after i finishes and finish before j starts.
      for (int k = i + 1; k < j; k++) {
        if (list[k].startTime > list[i].finishTime && list[k].finishTime < list[j].startTime) {
          if (C[i * n + k] + C[k * n + j] + 1 > C[i * n + j]) {
            C[i * n + j] = C[i * n + k] + C[k * n + j] + 1;
            S[i * n + j] = k;
          }
        }
      }
    }
  }
  printf("DP Algo: ");
  print_dp_activities(S, 0, n-1, n);
}

int main(int argc, char *argv[]) {
  activity list[N + 1] = {{0, 0, 0},
                          {1, 1, 4},
                          {2, 3, 5},
                          {3, 0, 6},
                          {4, 5, 7},
                          {5, 3, 9},
                          {6, 5, 9},
                          {7, 6, 10},
                          {8, 8, 11},
                          {9, 8, 12},
                          {10, 2, 14},
                          {11, 12, 16},
                          // dummy activity only for dp
                          {12, 20, 30}};
  int C[N + 1][N + 1], S[N + 1][N + 1];
  dp_activity_selector(list, N + 1, (int *)C, (int *)S);
  printf("\n");

  int counter = 0;
  activity selected[N];
  greedy_activity_selector(list, selected, &counter);
  printf("Greedy Algo: ");
  for (int i = 0; i < counter; i++)
    printf("%d ", selected[i].id);
  printf("\n");

  return 0;
}
