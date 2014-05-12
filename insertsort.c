#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define LENGTH 50
int array[LENGTH];
int array_used[LENGTH];
int array_used2[LENGTH+1];

void ArrayInit(int *array, int length){
  srand((unsigned)time(0));
  for(int i=0; i<length; ++i)
    array[i] = rand()%(length<<4);
}

void ArrayCopy(int *arraysrc, int *arraydst, int length){
  for(int i=0; i<length; ++i)
    arraydst[i] = arraysrc[i];
}

void ArrayView(int *array, int length){
  for(int i=0; i<length; ++i){
    if(i!=0 && 0==i%20) printf("\n");
	printf("%d ", array[i]);
  }
  printf("\n");
}

void InsertSort(int *array, int length){
  for(int i=1; i<length; ++i){
	if(array[i]>=array[i-1]) continue;
	int j;
    int val = array[i];
	for(j=i-1; j>=0&&array[j]>val; --j){
	  array[j+1] = array[j];
	}
	array[j+1] = val;
  }
}

void InsertSortGard(int *array, int length){
  for(int i=2; i<length; ++i){
	if(array[i]>=array[i-1]) continue;
    array[0] = array[i];
	int j;
	for(j=i-1; array[j]>array[0]; --j){
	  array[j+1] = array[j];
	}
	array[j+1] = array[0];
  }
}

int main(){
  struct timeval tbegin, tend;
  ArrayInit(array, LENGTH);
  ArrayView(array, LENGTH);

  printf("\nbegin straight insertion sort...\n");
  ArrayCopy(array, array_used, LENGTH);
  gettimeofday(&tbegin, NULL);
  InsertSort(array_used, LENGTH);
  gettimeofday(&tend, NULL);
  printf("end straight insertion sort!\n");
  ArrayView(array_used, LENGTH);
  printf("time usage: %ld usec  \n", (tend.tv_sec-tbegin.tv_sec)*1000000+tend.tv_usec-tbegin.tv_usec);
  
  printf("\nbegin straight insertion sort with gard...\n");
  ArrayCopy(array, array_used2+1, LENGTH);
  gettimeofday(&tbegin, NULL);
  InsertSortGard(array_used2, LENGTH+1);
  gettimeofday(&tend, NULL);
  printf("end straight insertion sort with gard!\n");
  ArrayView(array_used2+1, LENGTH);
  printf("time usage: %ld usec \n", (tend.tv_sec-tbegin.tv_sec)*1000000+tend.tv_usec-tbegin.tv_usec);

  return 0;
}
