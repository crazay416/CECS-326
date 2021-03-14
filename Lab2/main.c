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


void* merge(void* argv){
	struct sort halfOfArray = *(struct sort*) argv;
	int b[arraySize];
	int i;
	int currentIndex = 0;
	int down = 0;
	int up = halfOfArray.upperBound;
	
	while (down < halfOfArray.upperBound && up < arraySize){
		if(numArray[down] < numArray[up]){
			b[currentIndex++] = numArray[down++];
		}
		else{
			b[currentIndex++] = numArray[up++];
		}
	}

	
	while(down < halfOfArray.upperBound){
		b[currentIndex++] = numArray[down++];
	}
	
	while(up < arraySize){
		b[currentIndex] = numArray[up++];
	}
	
	for(i = 0; i < arraySize; i++){
		numArray[i] = b[i];
	}
	
	return NULL;



}

int main(){

	struct sort half[2];
	
	half[0].lowerBound = 0;
	half[0].upperBound = arraySize / 2;
	
	half[1].lowerBound = half[0].upperBound;
	half[1].upperBound = arraySize;
	
	pthread_t threads[2];
	
	for(int i = 0; i < 2; i++){
		pthread_create(&threads[i], NULL, bubbleSort, &half[i]);
	}
	
	for(int i = 0; i < 2; i++){
		pthread_join(threads[i], NULL);
	}
	
	pthread_t mergeThread;
	pthread_create(&mergeThread, NULL, merge, &half[0]);
	pthread_join(mergeThread, NULL);
	
	for(int i = 0; i < arraySize; i++){
		printf("%d, ", numArray[i]);
	}
	
	printf("\n\n");

}
