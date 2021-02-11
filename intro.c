#include <pthread.h>
#include <unistd.h>
#include <stdio.h>



void* myTurn(void * arg){
	for(int i = 0; i < 8; i++){
		sleep(1);
		printf("My Turn!: %d\n", i);
	}
	return NULL;
}

void yourTurn(){
	for(int i = 0; i < 3; i++){
		sleep(2);
		printf("Your turn!: %d\n", i);
	}

}

void ourTurn(){
	for(int i = 0; i < 6; i++){
		sleep(3);
		printf("Our Turn!: %d\n", i);
	}
}


int main(){
	pthread_t newthread;
	pthread_t thread;
	
	pthread_create(&newthread, NULL, myTurn, NULL);
	pthread_create(&thread, NULL, ourTurn, NULL);
	
	//myTurn();
	//ourTurn();
	yourTurn();
	
	pthread_join(&thread, NULL);
	pthread_join(&newthread, NULL);

}
