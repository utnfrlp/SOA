#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM_THREADS 5

void *task(void *t) {
  long id = (long) t;
  printf("Thread %ld started\n", id);

  long i;
  double result = 0.0;

  for (i = 0; i < 10000000; i++) {
    result = result + sin(i) * cos(i) * tan(i);
  }
  printf("Thread %ld completed with result %e\n", id, result);

  pthread_exit(0);
}

int main() {
  printf("Main started\n");

  long t;
  pthread_t thread[NUM_THREADS];
  long rc;

  for (t = 0; t < NUM_THREADS; t++) {
    printf("Creating thread %ld\n", t);
    rc = pthread_create(&thread[t], NULL, task, (void *) t);
    if (rc) {
      printf("ERROR: return code from pthread_create() is %ld\n", rc);
      exit(-1);
    }
  }

  printf("Main completed\n");
  pthread_exit(0);
}
