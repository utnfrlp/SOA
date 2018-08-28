#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define COUNTER_DONE 10
#define COUNTER_HALT1 3
#define COUNTER_HALT2 6

pthread_mutex_t counter_lock;
pthread_cond_t condition_var;

void *functionCount1();
void *functionCount2();
int counter = 0;

// Write numbers 1-3 and 8-10 as permitted by functionCount2()
void *functionCount1() {
  while (counter < COUNTER_DONE) {
      // Lock mutex and then wait for signal to relase mutex
      pthread_mutex_lock(&counter_lock);

      // Wait while functionCount2() operates on count
      // mutex unlocked if condition varialbe in functionCount2() signaled.
      pthread_cond_wait(&condition_var, &counter_lock);
      counter++;
      printf("Counter value functionCount1: %d\n", counter);

      pthread_mutex_unlock(&counter_lock);
   }

   pthread_exit(0);
}

// Write numbers 4-7
void *functionCount2() {
   while (counter < COUNTER_DONE) {
      pthread_mutex_lock(&counter_lock);

      if (counter < COUNTER_HALT1 || counter > COUNTER_HALT2) {
        // Condition of if statement has been met.
        // Signal to free waiting thread by freeing the mutex.
        // Note: functionCount1() is now permitted to modify "counter".
        pthread_cond_signal(&condition_var);
      } else {
        counter++;
        printf("Counter value functionCount2: %d\n", counter);
      }

      pthread_mutex_unlock(&counter_lock);
   }

   pthread_exit(0);
}

int main() {
   // printf("Main started\n");

   pthread_t thread1, thread2;

   // initialize pthread mutex and cond
   pthread_mutex_init(&counter_lock, NULL);
   pthread_cond_init(&condition_var, NULL);

   // create threads
   pthread_create(&thread1, NULL, functionCount1, NULL);
   pthread_create(&thread2, NULL, functionCount2, NULL);

   // block until all threads complete
   pthread_join(thread1, NULL);
   pthread_join(thread2, NULL);

   printf("Final counter: %d\n", counter);

   pthread_exit(0);
}
