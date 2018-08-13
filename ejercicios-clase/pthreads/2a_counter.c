#include <stdio.h>
#include <stdlib.h>
#define NUM_COUNTS 1000

long counter;

void count() {
  long i;

  for (i = 0; i < NUM_COUNTS; i++) {
    counter += i;
  }
}

int main() {
  // printf("Main started\n");

  count();

  printf("Result = %ld\n", counter);
}
