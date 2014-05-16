#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define LENGTH 50
int array[LENGTH];
int array_used[LENGTH];
int array_used2[LENGTH];

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

void Merge(int *array, int s1, int e1, int s2, int e2){
  int size = e1-s1+e2-s2+2;
  int *temp = array_used2;
  int i=0, j=s1, k=s2;
  while (i<size) {
	if (j>e1 || k>e2) break;
    if (array[j]<=array[k])	temp[i++] = array[j++];  
	else temp[i++] = array[k++];
  }  
  while (j <= e1) temp[i++] = array[j++];
  while (k <= e2) temp[i++] = array[k++];
  for (i=0,j=s1; i<size;)
    array[j++] = temp[i++];
}

void MergeSort(int *array, int s, int e){
  if (s<e) {
    int mid = (s+e)/2;
    MergeSort(array, s, mid);
    MergeSort(array, mid+1, e);
	Merge(array, s, mid, mid+1, e);
  }
}

void MergeSortNonRecur(int *array, int length){
  int step = 1;
  while (step < length) {
    for(int i=0; i<length; i+=step<<1){
	  if (i+2*step-1<length)
        Merge(array, i, i+step-1, i+step, i+2*step-1);     
	  else if (i+step < length)
        Merge(array, i, i+step-1, i+step, length-1);     
    }
	step = step<<1; 
  }
}

int main(){
  struct timeval tbegin, tend;
  ArrayInit(array, LENGTH);
  ArrayView(array, LENGTH);

  printf("\nbegin merge sort...\n");
  ArrayCopy(array, array_used, LENGTH);
  gettimeofday(&tbegin, NULL);
  MergeSort(array_used, 0, LENGTH-1);
  gettimeofday(&tend, NULL);
  printf("end merge sort!\n");
  ArrayView(array_used, LENGTH);
  printf("time usage: %ld usec \n", (tend.tv_sec-tbegin.tv_sec)*1000000+tend.tv_usec-tbegin.tv_usec);

  printf("\nbegin non-recurtive merge sort...\n");
  ArrayCopy(array, array_used, LENGTH);
  gettimeofday(&tbegin, NULL);
  MergeSortNonRecur(array_used, LENGTH);
  gettimeofday(&tend, NULL);
  printf("end non-recurtive merge sort!\n");
  ArrayView(array_used, LENGTH);
  printf("time usage: %ld usec \n", (tend.tv_sec-tbegin.tv_sec)*1000000+tend.tv_usec-tbegin.tv_usec);

  return 0;
}
