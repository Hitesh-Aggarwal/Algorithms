#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *compute_prefix_function(char *P, int m) {
  int *pi = malloc(sizeof(int) * m);
  pi[0] = 0;
  int k = 0;
  for (int q = 2; q <= m; q++) {
    while (k > 0 && P[k] != P[q - 1])
      k = pi[k];
    if (P[k] == P[q - 1]) k = k + 1;
    pi[q - 1] = k;
  }
  return pi;
}

void KMP_matcher(char *T, char *P) {
  int m = strlen(P);
  int *pi = compute_prefix_function(P,m);
  int q = 0;
  for (int i = 0; T[i] != '\0'; i++) {
    while (q > 0 && P[q] != T[i])
      q = pi[q - 1];
    if (P[q] == T[i]) q = q + 1;
    if (q == m) {
      printf("Pattern occurs with shift %d\n", i - m + 1);
      q = pi[q - 1];
    }
  }
  free(pi);
}

int main(int argc, char *argv[]) {
  char *T = "bacbabababacaab";
  char *P = "ababaca";
  KMP_matcher(T, P);
  printf("\n");
  return 0;
}
