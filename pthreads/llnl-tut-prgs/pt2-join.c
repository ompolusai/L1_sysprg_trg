/* pt2-join.c */
#define _POSIX_C_SOURCE    200112L	/* or earlier: 199506L */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS	2
//static int NUM_THREADS=2;

void *BusyWork(void *null)
{
	int i;
	double result = 0.0;
	for (i = 0; i < 1000000; i++) {
		result = result + 1;
		//result = result + (double)random();
	}
	printf("result = %f\n", result);
	pthread_exit((void *)0);
}

int main()
{
	pthread_t work_thrd[NUM_THREADS];
	pthread_attr_t attr;
	int rc, t, status;

	/* Initialize and set thread detached attribute */
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	printf("NUM_THREADS = %d\n", NUM_THREADS);
	for (t = 0; t < NUM_THREADS; t++) {
		printf("Creating thread %d\n", t);
		rc = pthread_create(&work_thrd[t], &attr, BusyWork, NULL);
		if (rc) {
			printf
			    ("ERROR; return code from pthread_create() is %d\n",
			     rc);
			exit(-1);
		}
	}

	/* Free attribute and wait for the other threads */
	pthread_attr_destroy(&attr);
	printf("NUM_THREADS = %d\n", NUM_THREADS);
	for (t = 0; t < NUM_THREADS; t++) {
			printf("join loop # %d\n", t);
		/* Note: "status" should not be local to the dying thread */
		rc = pthread_join(work_thrd[t], (void **)&status);
		if (rc) {
			printf("ERROR; return code from pthread_join() is %d\n",
			       rc);
			exit(-1);
		}
		printf("main: completed join with thread %d status %d\n", t, status);
		sleep(1);
	}

	pthread_exit(NULL);
}