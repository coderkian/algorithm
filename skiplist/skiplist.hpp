#ifndef SKIPLIST_HPP
#define SKIPLIST_HPP

#include <vector>

class ListNode{
  public:
    ListNode(int k, int s):key(k), forward(s, NULL) { }
    int key;
    std::vector<ListNode*> forward;
};

class SkipList{
  public:
    SkipList(int ml);
    ~SkipList();
    ListNode* SLsearch(int key);
    bool SLinsert(int key);
    bool SLdelete(int key);
    void SLreview();
    int RandomLevel();
  private:
    int level;
    ListNode* head;
    ListNode* tail;
    int maxlevel;
};

#endif
