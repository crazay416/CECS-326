#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>


struct sort{
	int upperBound;
	int lowerBound;
};

int numArray[] = {7, 12, 19, 3, 18, 4, 2, 6, 15, 8};
int arraySize = sizeof(numArray) / sizeof(numArray[0]);

void* bubbleSort(void* argv){
	int i;
	int j;
	
	struct sort halfOfArray = *(struct sort*) argv;
	int high = halfOfArray.upperBound;
	int low = halfOfArray.lowerBound;
	
	for(i = low; i < high - 1; i++){
		
		for(j = 0; j < high - i - 1; j++){
			
			if(numArray[j] > numArray[j+1]){
				int temp = numArray[j];
				numArray[j] = numArray[j + 1];
				numArray[j + 1] = temp;
			}
		}
	}
	return NULL;
}


int main(){

	
	struct sort structures[1];
	structures[0].lowerBound = 0;
	structures[0].upperBound = arraySize;
	pthread_t threads[1];
	
	for(int i = 0; i < 1; i++){
		pthread_create(&threads[i], NULL, bubbleSort, &structures);
	}
	
	for(int i = 0; i < 1; i++){
		pthread_join(threads[i], NULL);
	}
	
	for(int i = 0; i < arraySize; i++){
		printf("%d, ", numArray[i]);
	}

}
