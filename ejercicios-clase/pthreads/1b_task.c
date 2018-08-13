#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void task(long id) {
  printf("Task %ld started\n", id);

  long i;
  double result = 0.0;

  for (i = 0; i < 10000000; i++) {
    result = result + sin(i) * cos(i) * tan(i);
  }
  printf("Task %ld completed with result %e\n", id, result);
}

int main() {
  printf("Main started\n");

  long t;
  long num_threads = 5;

  for (t = 0; t < num_threads; t++) {
    task(t);
  }

  printf("Main completed\n");
}
