#include <pthread.h>
#include <unistd.h>
#include <stdio.h>


void* myTurn( void * arg){
	while(1){
		sleep(1);
		printf("My Turn!\n");
	}
	
	return NULL;
}


void yourTurn(){
	while(2){
		sleep(2);
		printf("Your Turn!\n");
	}

}
int main(){
	pthread_t newThread;
	
	pthread_create(&newThread, NULL, myTurn, NULL);
	
	//myTurn();
	yourTurn();

}
