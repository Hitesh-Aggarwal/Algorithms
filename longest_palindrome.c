#include <stdio.h>
#include <stdlib.h>

#define N 5
int X[N][N];
int B[N][N];

int max(int a, int b) { return (a > b) ? a : b; }

void palindrome(char *str) {
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      B[i][j] = -1;
  for (int i = 0; i < N; i++)
    X[i][i] = 1;
  for (int l = 2; l <= N; l++) {
    for (int i = 0; i < N - l + 1; i++) {
      int j = i + l - 1;
      if (str[i] == str[j]) {
        X[i][j] = X[i + 1][j - 1] + 2;
        B[i][j] = 0; // diagonal (bottom-right)
      } else {
        if (X[i + 1][j] > X[i][j - 1]) {
          X[i][j] = X[i + 1][j];
          B[i][j] = 1; // down
        } else {
          X[i][j] = X[i][j - 1];
          B[i][j] = 2; // left
        }
      }
    }
  }
}

void print_solution(char *str, int i, int j) {
  if (j < i)
    return;
  else if (j == i)
    printf("%c", str[i]);
  else if (B[i][j] == 0) {
    printf("%c", str[i]);
    print_solution(str, i + 1, j - 1);
    printf("%c", str[i]);
  } else if (B[i][j] == 1)
    print_solution(str, i + 1, j);
  else
    print_solution(str, i, j - 1);
}

int main(int argc, char *argv[]) {
  char str[N] = "civic";
  palindrome(str);
  print_solution(str, 0, N - 1);
  printf("\nLength of longest palindrome: %d\n", X[0][N - 1]);
  return 0;
}
