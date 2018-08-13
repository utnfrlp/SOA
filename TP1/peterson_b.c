#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM_THREADS	 2
#define MAX_COUNT 1000000L

volatile long count = 0;
volatile int estado[NUM_THREADS];
volatile int turno;

void e_peterson(int id) {
	int other = (id +1) % NUM_THREADS;

	estado[id] = 1;
	turno = other;
	__sync_synchronize();
	while (estado[other] && turno == other);
}

void s_peterson(int id) {
	estado[id] = 0;
}

void *counter(void *threadid) {
	long tid, i, max = MAX_COUNT/NUM_THREADS;
	tid = (long)threadid;

	for (i=0; i < max; i++) {
		e_peterson(tid);
		count++; //SC
		s_peterson(tid);
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
		rc = pthread_create(&threads[t], NULL, counter, (void *)t);
		if (rc){
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}

	for(t=0; t<NUM_THREADS; t++){
		pthread_join(threads[t], NULL);
	}

	float error = (MAX_COUNT-count)/(float) MAX_COUNT *100;

	printf("Final result: %ld Expected: %ld Diff: %ld Error: %3.2f%%\n", count, MAX_COUNT, count-MAX_COUNT, error);

	puts("Bye from main");
	pthread_exit(NULL);
}
