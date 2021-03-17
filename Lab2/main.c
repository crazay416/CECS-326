#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>


// Create a struct to divide the array from low to mid
// and mid + 1 to sizeofArray
struct sort{
	int upperBound;
	int lowerBound;
};

// Create the array to sort
int numArray[] = {7, 12, 19, 3, 18, 4, 2, 6, 15, 8};

// The number of values in the array
int arraySize = sizeof(numArray) / sizeof(numArray[0]);

// Algorithm to sort the array O(n^2)
void* bubbleSort(void* argv){
	int i;
	int j;
	int p;
	
	// Create a struct for part of the array
	struct sort halfOfArray = *(struct sort*) argv;
	int high = halfOfArray.upperBound;
	int low = halfOfArray.lowerBound;
	
	printf("This is array before:\n");
	for(int p = low; p < high; p++){
		printf("%d ", numArray[p]);
	}
	printf("\n\n");
	
	// Using Bubble Sort to sort array
	for(i = 0; i < high - 1; i++){
		
		for(j = 0; j < high - i - 1; j++){
			
			if(numArray[j] > numArray[j+1]){
				int temp = numArray[j];
				numArray[j] = numArray[j + 1];
				numArray[j + 1] = temp;
			}
		}
	}
	
	
	printf("This is array after:\n");
	for(int p = low; p < high; p++){
		printf("%d ", numArray[p]);
	}
	printf("\n\n");
	
	
	return NULL;
}

// Merge both arrays together
void* merge(void* argv){
	
	struct sort halfOfArray = *(struct sort*) argv;
	int b[arraySize];
	int i;
	int j;
	int currentIndex = 0;
	int down = 0;
	int up = halfOfArray.upperBound;
	
	// Merging arrays together if current value is greater
	// than next value its comparing to
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
	
	printf("\n");
	
	
	return NULL;



}

int main(){
	// Creating two structs
	struct sort half[2];
	
	// Settinng structs to certain parts
	// of numArray
	half[0].lowerBound = 0;
	half[0].upperBound = arraySize / 2;
	
	half[1].lowerBound = half[0].upperBound;
	half[1].upperBound = arraySize;
	
	// Creating 2 threads for both
	// halves of arrays
	pthread_t threads[2];
	
	printf("List Before sorting: \n");
	for(int i = 0; i < arraySize; i++){
		printf("%d ", numArray[i]);
	}
	printf("\n\n");
	
	for(int i = 0; i < 2; i++){
		pthread_create(&threads[i], NULL, bubbleSort, &half[i]);
	}
	
	for(int i = 0; i < 2; i++){
		pthread_join(threads[i], NULL);
	}
	
	pthread_t mergeThread;
	pthread_create(&mergeThread, NULL, merge, &half[0]);
	pthread_join(mergeThread, NULL);
	
	printf("Merging:\n");
	for(int i = 0; i < arraySize; i++){
		printf("%d ", numArray[i]);
	}
	
	printf("\n\n");

}
