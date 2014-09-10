#include <string.h>
#include <iostream>
#include "hashfun.h"

using std::size_t;
using std::cout; using std::endl; static unsigned int num = 4;

template <typename T>
struct equal_to 
{
  bool operator()(const T& lhs, const T& rhs) const
  {
    return lhs==rhs;
  }
};
template <> struct equal_to<const char*>
{
  bool operator()(const char* lhs, const char* rhs) {
    return strcmp(lhs, rhs)==0;
  }
};

template <typename T>
struct HashNode 
{
  HashNode(T &t):value(t), next(NULL) 
  { }
  HashNode<T> *next;
  T value;
};

template <typename T, typename hash_fun = hash<T>, typename com_fun = equal_to<T> >
class HashTable {
 public:
  HashTable(): bucketsize(num), entrynum(0),hash(), comfun(){
	bucket = new HashNode<T>*[num]; 
	memset(bucket, 0, num*sizeof(HashNode<T>*));
  }  
  ~HashTable(){
    clear();
  }
  HashNode<T>* insert(T v) {
    size_t index = getKey(v, bucketsize);
	  HashNode<T>* head=bucket[index];
	  while(head){
	    if(head->value == v) break;
	    head = head->next;
	  }
	  if(head) return head;
	  head = new HashNode<T>(v);
	  head->next = bucket[index];
	  bucket[index] = head;
	  ++entrynum;
	  if(entrynum > bucketsize*2) 
	    RebuildHashTable();
	  return head;
  }
  HashNode<T>* find(T v) {
	for(int i=0; i<bucketsize; ++i) {
	  HashNode<T> *node = bucket[i];
	  while(node){
	    if(comfun(node->value, v)) return node;
		node = node->next;
	  }
	}
	return NULL; 
  }
  void printAll() {
	for(int i=0; i<bucketsize; ++i) {
	  cout<<"bucket ["<<i<<"]:"<<endl;
	  HashNode<T> *node = bucket[i];
	  while(node) {
	    cout<<node->value<<" ";
		node = node->next;
	  }
	  cout<<endl;
	}
	cout<<" total: "<<entrynum<<endl;
  }
 private:
  HashNode<T> **bucket;
  unsigned int bucketsize;
  unsigned int entrynum;
  hash_fun hash;
  com_fun comfun;
  size_t getKey(T value, int n) { return hash(value)%n; }
  void clear() {
	for(int i=0; i<bucketsize; ++i) {
	  HashNode<T> *node = bucket[i];
	  while(node){
	    HashNode<T> *tmp = node->next;
		delete node;
		node = tmp;
	  }
    } 
	delete [] bucket;
  }
  void RebuildHashTable() {
    int size = bucketsize<<2;
    HashNode<T> **newbucket = new HashNode<T>*[size];
	memset(newbucket, 0, size*sizeof(HashNode<T>*));
	for(int i=0; i<bucketsize; ++i) {
	  HashNode<T> *node = bucket[i];
	  while(node){
	    size_t index = getKey(node->value, size);
		HashNode<T>* tmp = node->next;
		node->next = newbucket[index];
		newbucket[index] = node;
		node = tmp;
	  }
	}
	delete [] bucket;
	bucket = newbucket;
	bucketsize = size;
  }
};
