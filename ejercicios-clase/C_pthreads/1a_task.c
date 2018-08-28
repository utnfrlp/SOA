#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void task() {
  printf("Task started\n");

  long i;
  double result = 0.0;
  
  for (i = 0; i < 10000000; i++) {
    result = result + sin(i) * cos(i) * tan(i);
  }
  printf("Task completed with result %e\n", result);
}

int main() {
  printf("Main started\n");

  task();

  printf("Main completed\n");
}
