#include <limits.h>
#include <stdio.h>

#define N 16

void find_max_crossing_subarray(
    int arr[], int low, int mid, int high, int *left, int *right, int *max_sum) {

  int left_sum = INT_MIN;
  int sum = 0;
  int i = mid;
  while (i >= low) {
    sum += arr[i];
    if (sum > left_sum) {
      left_sum = sum;
      *left = i;
    }
    i = i - 1;
  }
  int right_sum = INT_MIN;
  sum = 0;
  int j = mid + 1;
  while (j <= high) {
    sum += arr[j];
    if (sum > right_sum) {
      right_sum = sum;
      *right = j;
    }
    j = j + 1;
  }
  *max_sum = left_sum + right_sum;
}

void find_max_subarray(int arr[], int low, int high, int *l, int *h, int *max_sum) {
  if (low == high) {
    *l = low;
    *h = high;
    *max_sum = arr[low];
  } else {
    int left_left, left_right, left_sum;
    int cross_left, cross_right, cross_sum;
    int right_left, right_right, right_sum;
    int mid = low + (high - low) / 2;
    find_max_subarray(arr, low, mid, &left_left, &left_right, &left_sum);
    find_max_subarray(arr, mid + 1, high, &right_left, &right_right, &right_sum);
    find_max_crossing_subarray(arr, low, mid, high, &cross_left, &cross_right, &cross_sum);
    if (left_sum > right_sum && left_sum > cross_sum) {
      *l = left_left;
      *h = left_right;
      *max_sum = left_sum;
    } else if (right_sum > left_sum && right_sum > cross_sum) {
      *l = right_left;
      *h = right_right;
      *max_sum = right_sum;
    } else {
      *l = cross_left;
      *h = cross_right;
      *max_sum = cross_sum;
    }
  }
}

void max_subarray(int A[], int n, int *l, int *h, int *max_sum) {
  int current_sum = A[0];
  int p = 0;
  int q;
  *max_sum = INT_MIN;
  for (int i = 1; i < n; i++) {
    int val = current_sum + A[i];
    if (val >= A[i]) {
      current_sum = val;
      q = i;
    } else {
      current_sum = A[i];
      p = i;
      q = i;
    }
    if (*max_sum < current_sum) {
      *max_sum = current_sum;
      *l = p;
      *h = q;
    }
  }
}

int main() {
  int arr[N] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
  int low, high, sum;
  max_subarray(arr, N, &low, &high, &sum);
  printf("%d %d %d\n", low, high, sum);
  return 0;
}
