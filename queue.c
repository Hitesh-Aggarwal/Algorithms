#include <stdio.h>
#define N 11

void *queue[N];
void **tail;
void **head;

#define is_empty() (tail == head)
#define is_full() (head = tail + 1)

void enqueue(void *x) {
  *tail = x;
  if (tail == queue + N - 1)
    tail = queue;
  else
    tail++;
}

void *dequeue() {
  void *x = *head;
  if (head == queue + N - 1)
    head = queue;
  else
    head++;
  return x;
}

int main(int argc, char *argv[]) {
  tail = queue;
  head = queue;
  int a= 10;
  int b = 20;
  int c = 12;
  int d = 23;
  enqueue(&a);
  enqueue(&b);
  enqueue(&c);
  enqueue(&d);
  while (!is_empty())
    printf("%d\n", *(int*)dequeue());
  return 0;
}
