#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define LENGTH 50
#define MAXNUM 200
int array[LENGTH];
int array_sort[LENGTH];
int array_count[MAXNUM];

void ArrayInit(int *array, int length){
  srand((unsigned)time(0));
  for(int i=0; i<length; ++i)
    array[i] = rand()%(MAXNUM);
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

void CountingSort(int *array, int length){
  for(int i=0; i<length; ++i)
    array_count[array[i]]++;
  for(int j=1; j<MAXNUM; ++j)
    array_count[j] += array_count[j-1];
  for(int i=0; i<length; ++i) {
    array_sort[array_count[array[i]]] = array[i];
    array_count[array[i]]--;
  }

}


int main(){
  struct timeval tbegin, tend;
  ArrayInit(array, LENGTH);
  ArrayView(array, LENGTH);

  printf("\nbegin straight insertion sort...\n");
  gettimeofday(&tbegin, NULL);
  CountingSort(array, LENGTH);
  gettimeofday(&tend, NULL);
  printf("end straight insertion sort!\n");
  ArrayView(array_sort, LENGTH);
  printf("time usage: %ld usec  \n", (tend.tv_sec-tbegin.tv_sec)*1000000+tend.tv_usec-tbegin.tv_usec);
  
  return 0;
}
