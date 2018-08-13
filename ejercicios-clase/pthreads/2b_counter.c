#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 1000

long counter = 0;

void *count(void *t) {
  long value = (long) t;

  counter += value;
  // printf("partial result = %ld\n", counter);

  pthread_exit(0);
}

int main() {
  // printf("Main started\n");

  long t;
  pthread_t thread[NUM_THREADS];
  long rc;

  for (t = 0; t < NUM_THREADS; t++) {
    rc = pthread_create(&thread[t], NULL, count, (void *) t);
    if (rc) {
      printf("ERROR: return code from pthread_create() is %ld\n", rc);
      exit(-1);
    }
  }

  // block until all threads complete
  for (t = 0; t < NUM_THREADS; ++t) {
    pthread_join(thread[t], NULL);
  }

  printf("Result = %ld\n", counter);
  pthread_exit(0);
}
