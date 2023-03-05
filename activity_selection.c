#include <stdio.h>

#define N 12

typedef struct activity {
  int id;
  int startTime;
  int finishTime;
} activity;

void recursive_activity_selector(activity *list, int k, activity *selected,
                                 int *counter) {
  int m = k + 1;
  while (m < N && list[m].startTime < list[k].finishTime)
    m = m + 1;
  if (m < N) {
    selected[*counter] = list[m];
    *counter = *counter + 1;
    recursive_activity_selector(list,m,selected,counter);
  }
}

int main(int argc, char *argv[]) {
  activity list[N] = {{0, 0, 0},  {1, 1, 4},  {2, 3, 5},   {3, 0, 6},
                      {4, 5, 7},  {5, 3, 9},  {6, 5, 9},   {7, 6, 10},
                      {8, 8, 11}, {9, 8, 12}, {10, 2, 14}, {11, 12, 16}};
  int counter = 0;
  activity selected[N];
  recursive_activity_selector(list,0,selected,&counter);
  for(int i=0; i<counter; i++)
    printf("%d ", selected[i].id);
  printf("\n");
  return 0;
}
