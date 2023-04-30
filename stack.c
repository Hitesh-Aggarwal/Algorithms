#include <stdio.h>

#define N 10

void *stack[N];
void **ptr;

#define push(x) (*(ptr++) = x)
#define pop() (*(--ptr))
#define is_empty() (ptr == stack)

int main(int argc, char *argv[]) {
  ptr = stack;
  int a = 10;
  int b = 30;
  int c = 1;
  push(&a);
  push(&b);
  push(&c);
  while (!is_empty())
    printf("%d\n", *(int*)pop());
  return 0;
}
