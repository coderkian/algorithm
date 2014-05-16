#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define LENGTH 100

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

void Quicksort1(int *array, int b, int e) {
  if (b >= e) return;
  int low = b, high = e, val = array[e];
  while(low < high) {
    while(low<=high && array[high]>=val) --high;
	if(low<high) swap(&array[low], &array[high]);
    while(low<=high && array[low]<=val) ++low;
	if(low<high) swap(&array[low], &array[high]);
  }
  swap(&array[e], &array[low]);
  Quicksort1(array, b, low-1);
  Quicksort1(array, low+1, e);
}

void Quicksort2(int *array, int b, int e) {
  if(b>=e) return;
  int i,j;
  for(i=b,j=b; j<e;){
    if(array[j]<array[e]) {
      if(i!=j)
        swap(&array[i], &array[j]);
      ++i;++j;
    } else {
      ++j;
    }
  }
  swap(&array[i], &array[e]);
  Quicksort2(array, b, i-1);
  Quicksort2(array, i+1, e);
}
int main(){
  struct timeval tbegin, tend;

  ArrayInit(array, LENGTH);
  ArrayView(array, LENGTH);
  printf("\nbegin quick sort1...\n");
  ArrayCopy(array, array_used, LENGTH);
  gettimeofday(&tbegin, NULL);
  Quicksort1(array_used, 0, LENGTH-1);
  gettimeofday(&tend, NULL);
  printf("end quick sort1!\n");
  ArrayView(array_used, LENGTH);
  printf("time usage: %ld usec \n", (tend.tv_sec-tbegin.tv_sec)*1000000+tend.tv_usec-tbegin.tv_usec);

  printf("\nbegin quick sort2...\n");
  ArrayCopy(array, array_used, LENGTH);
  gettimeofday(&tbegin, NULL);
  Quicksort2(array_used, 0, LENGTH-1);
  gettimeofday(&tend, NULL);
  printf("end quick sort2!\n");
  ArrayView(array_used, LENGTH);
  printf("time usage: %ld usec \n", (tend.tv_sec-tbegin.tv_sec)*1000000+tend.tv_usec-tbegin.tv_usec);
}
