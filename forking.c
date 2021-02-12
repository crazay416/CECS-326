#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


int main(int argc, char* arg[]){
	fork();
	int id = fork();
	//if(id != 0){
	//	fork();
	//}
	printf("ForkId: %i\n", id);
	//printf("Hello world\n");
	return 0;
}
