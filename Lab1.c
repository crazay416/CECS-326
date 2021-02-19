#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int SharedVariable = 0;

pthread_barrier_t barrier;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* SimpleThread(void *which){
	int num, val;
	
	int* iptr = (int *)which;
	
	
	for(num = 0; num < 20; num++){
		if(random() > RAND_MAX / 2)
		usleep(500);
		
	#ifdef PTHREAD_SYNC
		pthread_mutex_lock(&mutex);
	#endif	
		
		val = SharedVariable;
		printf("*** thread %d sees value %d\n", *iptr, val);
		SharedVariable = val + 1;
	#ifdef PTHREAD_SYNC
		pthread_mutex_unlock(&mutex);
	#endif
	}
	
	
	pthread_barrier_wait(&barrier);
	
	val = SharedVariable;
	printf("Thread %d sees final value %d\n", *iptr, val);
}


int main(int argc,char **argv){
	if(argc < 2){
		printf("Less than what is expected\n");
		exit(-1);
	}
	
	int n_threads = atoi(argv[1]);
	
	pthread_t threads[n_threads];
	int args[n_threads];
	
	pthread_barrier_init(&barrier, NULL, n_threads);
	
	int i;
	for(i = 0; i < n_threads; i++){
		args[i] = i;
	}
	
	for(i = 0; i < n_threads; i++){
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&threads[i], &attr, SimpleThread, &args[i]);
	}
	
	for(i = 0; i < n_threads; i++){
		pthread_join(threads[i], NULL);
	}


}
