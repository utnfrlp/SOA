#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS	 2
#define MAX_COUNT 100000000L


volatile long count = 0;

void *counter(void *threadid) {
	long tid, i, max = MAX_COUNT/NUM_THREADS;
	tid = (long)threadid;

	for (i=0; i < max; i++) {
		count++;
	}

	pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
	pthread_t threads[NUM_THREADS];
	int rc;
	long t;

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

	printf("Final value: %ld Expected: %ld Error: %3.2f%%\n", count, MAX_COUNT, error);

	printf("Bye from main");
	pthread_exit(NULL);
}
