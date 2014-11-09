#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <limits>
#include "skiplist.hpp"



SkipList::SkipList(int ml):level(0), maxlevel(ml) {
  head = new ListNode(std::numeric_limits<int>::min(), maxlevel);
  tail = new ListNode(std::numeric_limits<int>::max(), 1);
  for (auto it=head->forward.begin(); it!=head->forward.end(); ++it)
    *it = tail;
  srand(time(0));
}

SkipList::~SkipList(){
  ListNode* ite = head;
  while (ite) {
    ListNode* node = ite;
    ite = ite->forward[0];
    delete node;
  }
}

int SkipList::RandomLevel(){
  int level = 1;
  int rl = 0;
  while(rl=rand(), rl%2) 
    ++level;
  return level>maxlevel? maxlevel:level;
}

ListNode* SkipList::SLsearch(int key) {
    int l = level;
    ListNode* currnode = head;
    ListNode* nextnode=NULL;
    std::cout<<"search "<<key<<" path: ";
    for (int l = level-1; l>=0; --l){
      while (nextnode=currnode->forward[l], nextnode->key<key) {
        currnode = nextnode;
        std::cout<<"--"<<currnode->key;
      }
    }
    std::cout<<std::endl;
    if (nextnode->key == key) return nextnode;
    return NULL;
}

bool SkipList::SLinsert(int key){
  std::vector<ListNode*> update(maxlevel, head);
  ListNode* currnode = head;
  ListNode* nextnode = currnode->forward[level-1>=0?level:0];
  for (int l = level-1; l>=0; --l){
    while (nextnode=currnode->forward[l], nextnode->key<key)
      currnode = nextnode;
    update[l] = currnode;
  }
  if (nextnode->key == key) return false;
  int rl = RandomLevel();
  std::cout<<"key="<<key<<" level="<<rl<<std::endl;
  if (rl>level) level = rl;
  ListNode* node = new ListNode(key, rl);
  while (--rl>=0){
    node->forward[rl] = update[rl]->forward[rl];
    update[rl]->forward[rl] = node;
  }
  return true; 
}

bool SkipList::SLdelete(int key) {
  std::vector<ListNode*> update(level, NULL);
  ListNode* currnode = head; 
  ListNode* nextnode=NULL;
  for (int l = level-1; l>=0; --l){
    while (nextnode=currnode->forward[l], nextnode->key<key)
      currnode = nextnode;
    update[l] = currnode;
  }
  if (nextnode->key != key) return false;
  for (int i=0; i<level; ++i){
    if (update[i]->forward[i] == nextnode) 
      update[i]->forward[i] = nextnode->forward[i];
    else
      break;
  }
  delete nextnode;
  int l = level-1;
  while (l>=0 && head->forward[l]==tail) --l;
  level = l+1;
  return true;
}

void SkipList::SLreview() {
  std::cout<<"SkipList review: "<<std::endl;
  for (int l = level-1; l>=0; --l) {
    ListNode* p = head->forward[l];
    while (p != tail) {
      std::cout<<p->key<<" ";
      p = p->forward[l];
    }
    std::cout<<std::endl;
  }
}

int main() {
  int input[] = {7, 9, 3, 2, 6, 11, 4, 10, 8, 1, 5 };
  SkipList sl(4);
  for(int num: input){
    if (sl.SLinsert(num))
      std::cout<<"intsert "<<num<<" success!"<<std::endl;
    else
      std::cout<<"intsert "<<num<<" failed!"<<std::endl;
  }
  sl.SLreview();
  if (ListNode* p = sl.SLsearch(10))
    std::cout<<"search 10 success "<<std::endl;
  else
    std::cout<<"search 10 failed "<<std::endl;
  sl.SLdelete(10);
  std::cout<<"delete 10 "<<std::endl;
  sl.SLreview();
}


