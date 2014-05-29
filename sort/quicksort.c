#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <utility>


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

int partition1(int *array, int low, int high) {
  int val = array[low];
  while(low < high) {
    while(low<high && array[high]>=val) --high;
    swap(&array[low], &array[high]);
    while(low<high && array[low]<=val) ++low;
    swap(&array[low], &array[high]);
  }
  return low;
}

void Quicksort1(int *array, int b, int e) {
  if (b >= e) return;
  int p = partition1(array, b, e);
  Quicksort1(array, b, p-1);
  Quicksort1(array, p+1, e);
}

int partition2(int *array, int low, int high) {
  int i,j;
  for(i=low,j=low; j<high;){
    if(array[j]<array[high]) {
      if(i!=j)
        swap(&array[i], &array[j]);
      ++i;++j;
    } else {
      ++j;
    }
  }
  return i;
}

void Quicksort2(int *array, int b, int e) {
  if(b>=e) return;
  int p = partition2(array, b, e);
  swap(&array[p], &array[e]);
  Quicksort2(array, b, p-1);
  Quicksort2(array, p+1, e);
}

void QuicksortNonRecur(int *array, int b, int e) {
  if (b >= e) return;
  std::stack< std::pair<int, int> > stk;
  stk.push(std::make_pair(b, e));
  while(!stk.empty()) {
    std::pair<int, int> pair = stk.top();
    stk.pop();
    if(pair.first >= pair.second) continue;
    int p = partition1(array, pair.first, pair.second);
    if(p < pair.second) stk.push(std::make_pair(p+1, e));
    if(p > pair.first) stk.push(std::make_pair(b, p-1));
  }
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

  printf("\nbegin quick sort nonrecur...\n");
  ArrayCopy(array, array_used, LENGTH);
  gettimeofday(&tbegin, NULL);
  QuicksortNonRecur(array_used, 0, LENGTH-1);
  gettimeofday(&tend, NULL);
  printf("end quick sort nonrecur!\n");
  ArrayView(array_used, LENGTH);
  printf("time usage: %ld usec \n", (tend.tv_sec-tbegin.tv_sec)*1000000+tend.tv_usec-tbegin.tv_usec);
}
