#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define NUM_THREADS      4
#define MAX_COUNT 10000000


// utlizado para guardar los índices de los ID
struct thread_data {
    int tid;
};

int counter = 0;
int choosing[NUM_THREADS];
int number[NUM_THREADS];

int max(int *v, int size) {
    int max = 0, i = 0;
    for (i=0; i<size; i++) {
        if (v[i] > max) {
            max = v[i];
        }
    }
    return max;
}

void lock(int i) {
    int j;

    choosing[i] = 1;
    __atomic_thread_fence(__ATOMIC_RELEASE);
    number[i] = max(number, NUM_THREADS) + 1;
    __atomic_thread_fence(__ATOMIC_SEQ_CST); //__sync_synchronize();
    choosing[i] = 0;

    for (j=0; j<NUM_THREADS; j++) {
        while(choosing[j]);
        while(number[j] > 0 &&
            (number[j] < number[i] ||
            (number[j] == number[i] && j < i)));
    }
}

void unlock(int i) {
    number[i] = 0;
}

void *count(void *ptr) {
    long i, max = MAX_COUNT/NUM_THREADS;
    int tid = ((struct thread_data *) ptr)->tid;

    for (i=0; i < max; i++) {
        lock(tid);
        counter += 1;
        unlock(tid);
    }

    printf("End %d counter: %d\n", tid, counter);
    return 0;
}

int main (int argc, char *argv[]) {
    pthread_t threads[NUM_THREADS];
    int rc, i;
    struct thread_data id[NUM_THREADS];

    for(i=0; i<NUM_THREADS; i++){
        id[i].tid = i;
        rc = pthread_create(&threads[i], NULL, count, (void *) &id[i]);
    }

    for(i=0; i<NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    float error = (MAX_COUNT-counter)/(float) MAX_COUNT *100;

	printf("Final value: %d Expected: %d Diff: %d Error: %3.2f%%\n", counter, MAX_COUNT, counter-MAX_COUNT, error);
    
    printf("Bye from main");
    pthread_exit(NULL);
}
