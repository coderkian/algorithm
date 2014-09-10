#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
#include <iterator>
#include <ctime>
#include <sys/time.h>

#define LENGTH 10

using namespace std;

int partition1(vector<int> &array, int low, int high) {
  int val = array[low];
  while(low < high) {
    while(low<high && array[high]>=val) --high;
    array[low] = array[high];
    while(low<high && array[low]<=val) ++low;
    array[high] = array[low];
  }
  array[low] = val;
  return low;
}

void Quicksort1(vector<int> &array, int b, int e) {
  if (b >= e) return;
  int p = partition1(array, b, e);
  Quicksort1(array, b, p-1);
  Quicksort1(array, p+1, e);
}

int partition2(vector<int> &array, int low, int high) {
  int i,j;
  for(i=low,j=low; j<high;){
    if(array[j]<array[high]) {
      if(i!=j)
        swap(array[i], array[j]);
      ++i;++j;
    } else {
      ++j;
    }
  }
  return i;
}

void Quicksort2(vector<int> &array, int b, int e) {
  if(b>=e) return;
  int p = partition2(array, b, e);
  swap(array[p], array[e]);
  Quicksort2(array, b, p-1);
  Quicksort2(array, p+1, e);
}

void QuicksortNonRecur(vector<int> &array, int b, int e) {
  if (b >= e) return;
  stack< pair<int, int> > stk;
  stk.push(make_pair(b, e));
  while(!stk.empty()) {
    pair<int, int> pair = stk.top();
    stk.pop();
    if(pair.first >= pair.second) continue;
    int p = partition1(array, pair.first, pair.second);
    if(p < pair.second) stk.push(make_pair(p+1, e));
    if(p > pair.first) stk.push(make_pair(b, p-1));
  }
}

int main(){
  struct timeval tbegin, tend;
  vector<int> array(LENGTH), array_used(LENGTH);

  srand(time(0));
  generate(array.begin(), array.end(), [&](){return rand()%LENGTH; });
  copy(array.begin(), array.end(), ostream_iterator<int>(cout, " "));
  cout<<endl;
  copy(array.begin(), array.end(), array_used.begin());
  gettimeofday(&tbegin, NULL);
  Quicksort1(array_used, 0, LENGTH-1);
  gettimeofday(&tend, NULL);
  copy(array_used.begin(), array_used.end(), ostream_iterator<int>(cout, " "));
  cout<<endl;
  printf("Quicksort1 time usage: %ld usec \n", (tend.tv_sec-tbegin.tv_sec)*1000000+tend.tv_usec-tbegin.tv_usec);

  copy(array.begin(), array.end(), array_used.begin());
  gettimeofday(&tbegin, NULL);
  Quicksort2(array_used, 0, LENGTH-1);
  gettimeofday(&tend, NULL);
  copy(array_used.begin(), array_used.end(), ostream_iterator<int>(cout, " "));
  cout<<endl;
  printf("Quicksort2 time usage: %ld usec \n", (tend.tv_sec-tbegin.tv_sec)*1000000+tend.tv_usec-tbegin.tv_usec);

  copy(array.begin(), array.end(), array_used.begin());
  gettimeofday(&tbegin, NULL);
  QuicksortNonRecur(array_used, 0, LENGTH-1);
  gettimeofday(&tend, NULL);
  copy(array_used.begin(), array_used.end(), ostream_iterator<int>(cout, " "));
  cout<<endl;
  printf("QuicksortNonRecur time usage: %ld usec \n", (tend.tv_sec-tbegin.tv_sec)*1000000+tend.tv_usec-tbegin.tv_usec);
}
