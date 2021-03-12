#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct sort{
	int upperBound;
	int lowerBound;
}

int numArray[] = {7, 12, 19, 3, 18, 4, 2, 6, 15, 8};
int arraySize = sizeof(numArray) / sizeof(numArray[0]);

void* bubbleSort(void* argv){
	int i;
	struct sort halfOfArray = *(struct sort*) argv;
	int high = halfOfArray.upperBound;
	int low = halfOfArray.lowerBound;
	for(i = low; high < )


}


int main(){
	int i;
	for(i = 0; i < arraySize; i++){
		printf("%d\n", numArray[i]);
	}

}
