#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define NUM 10
#define NUM2 (NUM*NUM)

int array[NUM];
int array_tmp[NUM];
int array_count[NUM];

void ArrayInit(int *array){
  srand((unsigned)time(0));
  for(int i=0; i<NUM; ++i){
    array[i] = rand()%NUM2;
  }
}

void ArrayReset(int *array) {
  for(int i=0; i<NUM; ++i)
    array[i] = 0;
}

void ArrayView(int *array){
  for(int i=0; i<NUM; ++i)
    printf("%d ", array[i]);
  printf("\n");
}

void ArrayCopy(int *src, int *des) {
  for (int i=0; i<NUM; ++i)
    des[i] = src[i];
}
int RadixSort(int *array) {
  for(int i=0; i<2; ++i) {
    for(int j=0; j<NUM; ++j){
      int r = i, index = array[j];
      while (r-->0) index /= NUM;
      array_count[index%NUM]++;
    }
    for(int k=1; k<NUM; ++k)
      array_count[k] += array_count[k-1];
    for(int m=NUM-1; m>=0; --m){
      int r = i, index = array[m];
      while (r-->0) index /= NUM;
      array_tmp[array_count[index%NUM]-1] = array[m];
      array_count[index%NUM]--;
    }
    ArrayCopy(array_tmp, array);
    ArrayReset(array_count);
  }
}

int main(){
  ArrayInit(array);
  ArrayView(array);
  RadixSort(array);
  ArrayView(array);
}
