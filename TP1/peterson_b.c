#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_THREADS 2
#define MAX_COUNT 10000000


int counter = 0;
int estado[NUM_THREADS];
int turno;

void lock(int id) {
	int other = (id +1) % NUM_THREADS;

	estado[id] = 1;
	turno = other;
	__atomic_thread_fence(__ATOMIC_SEQ_CST); //__sync_synchronize();

	while (estado[other] && turno == other);
}

void unlock(int id) {
	estado[id] = 0;
}

void *count(void *threadid) {
	long tid, i, max = MAX_COUNT/NUM_THREADS;
	tid = (long)threadid;

	for (i=0; i < max; i++) {
		lock(tid);
		counter++; // seccción crítica, nuestra variable global
		unlock(tid);
	}

	pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
	pthread_t threads[NUM_THREADS];
	int rc;
	long t;

	estado[0] = 0;
	estado[1] = 0;
	turno = 0;

	for(t=0; t<NUM_THREADS; t++){
		rc = pthread_create(&threads[t], NULL, count, (void *)t);
		if (rc){
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}

	for(t=0; t<NUM_THREADS; t++){
		pthread_join(threads[t], NULL);
	}

	float error = (MAX_COUNT-counter)/(float) MAX_COUNT *100;

	printf("Final value: %d Expected: %d Diff: %d Error: %3.2f%%\n", counter, MAX_COUNT, counter-MAX_COUNT, error);

	printf("Bye from main");
	pthread_exit(NULL);
}
