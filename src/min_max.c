#include "min_max.h"

void min_and_max(int *arr, int n, int *min, int *max) {
  if (n < 1)
    return;
  int i;
  if (n % 2 == 1) {
    *min = arr[0];
    *max = arr[0];
    i = 1;
  } else {
    if (arr[0] > arr[1]) {
      *min = arr[1];
      *max = arr[0];
    } else {
      *min = arr[0];
      *max = arr[1];
    }
    i = 2;
  }
  while (i < n) {
    if (arr[i] < arr[i+1]) {
      if (arr[i] < *min) *min = arr[i];
      if (arr[i+1] > *max) *max = arr[i+1];
    }
    else {
      if (arr[i+1] < *min) *min = arr[i+1];
      if (arr[i] > *max) *max = arr[i];
    }
    i+=2;
  }
}
