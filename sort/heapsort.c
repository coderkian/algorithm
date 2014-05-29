#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define LENGTH 10
int array[LENGTH];
int array_used[LENGTH];
int array_used2[LENGTH+1];

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
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


void MaxHeap(int *array, int i, int length) {
  int l = (i<<1)+1;
  int r = (i<<1)+2;
  int largest = i;
  if (l<=length && array[i]<array[l])
    largest = l;
  if(r<=length && array[largest]<array[r])
    largest = r;
  if(largest != i) {
    swap(&array[i],&array[largest]);
    MaxHeap(array, largest, length);
  }
}

void BuildMaxHeap(int *array, int length){
  for(int i=(length>>1)-1; i>=0; --i)
    MaxHeap(array, i, length);
}

void HeapSort(int *array, int length) {
  BuildMaxHeap(array, length);
  for(int i=length-1; i>0; --i){
    swap(&array[i], &array[0]);
    length--;
    MaxHeap(array, 0, length-1);
  }
}

int main(){
  struct timeval tbegin, tend;
  ArrayInit(array, LENGTH);
  ArrayView(array, LENGTH);
  printf("\nbegin heap sort...\n");
  ArrayCopy(array, array_used, LENGTH);
  gettimeofday(&tbegin, NULL);
  HeapSort(array_used, LENGTH);
  gettimeofday(&tend, NULL);
  printf("end heap sort!\n");
  ArrayView(array_used, LENGTH);
  printf("time usage: %ld usec \n", (tend.tv_sec-tbegin.tv_sec)*1000000+tend.tv_usec-tbegin.tv_usec);
}
