#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t counter_1_lock;
pthread_mutex_t counter_2_lock;

void *functionInc();
void *functionDec();
int counter_1 = 0;
int counter_2 = 0;

void *functionInc() {
    pthread_mutex_lock(&counter_1_lock);
    printf("INC: Lock counter_1_lock\n");
    pthread_mutex_lock(&counter_2_lock);
    printf("INC: Lock counter_2_lock\n");

    counter_1+=10;
    counter_2+=10;

    pthread_mutex_unlock(&counter_2_lock);
    printf("INC: Unlock counter_2_lock\n");
    pthread_mutex_unlock(&counter_1_lock);
    printf("INC: Unlock counter_1_lock\n");

    pthread_exit(0);
}

void *functionDec() {
    pthread_mutex_lock(&counter_2_lock);
    printf("DEC: Lock counter_2_lock\n");


    // this new approach is non-blocking, while common lock is blocking
    while (pthread_mutex_trylock(&counter_1_lock)) {
      pthread_mutex_unlock(&counter_2_lock);
      pthread_mutex_lock(&counter_2_lock);
    }
    // pthread_mutex_lock(&counter_1_lock);
    printf("DEC: Lock counter_1_lock\n");

    counter_2-=10;
    counter_1-=10;

    pthread_mutex_unlock(&counter_1_lock);
    printf("DEC: Unlock counter_1_lock\n");
    pthread_mutex_unlock(&counter_2_lock);
    printf("DEC: Unlock counter_2_lock\n");

    pthread_exit(0);
}

int main() {
   // printf("Main started\n");

   pthread_t thread1, thread2;

   // initialize pthread mutexes
   pthread_mutex_init(&counter_1_lock, NULL);
   pthread_mutex_init(&counter_2_lock, NULL);

   // create threads
   pthread_create(&thread1, NULL, functionInc, NULL);
   pthread_create(&thread2, NULL, functionDec, NULL);

   // block until all threads complete
   pthread_join(thread1, NULL);
   pthread_join(thread2, NULL);

   printf("Final counter_1: %d\n", counter_1);
   printf("Final counter_2: %d\n", counter_2);

   pthread_exit(0);
}
