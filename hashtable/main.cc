#include <iostream>
#include "hashtable.h"

int main(){
  HashTable<int> ht;
  ht.insert(1);
  ht.insert(4);
  ht.insert(7);
  ht.insert(9);
  ht.insert(11);
  ht.insert(22);
  ht.insert(15);
  ht.insert(5);
  ht.insert(50);

  ht.printAll();

  HashNode<int> *node1 = ht.find(7);
  if(node1) cout<<"find "<<node1->value<<endl;

  HashTable<const char*> htchar;
  htchar.insert("aaa");
  htchar.insert("bbb");
  htchar.insert("ccc");
  htchar.insert("ddd");
  htchar.insert("eee");

  htchar.printAll();
  HashNode<const char*> *node2 = htchar.find("ccc");
  if(node2) cout<<"find "<<node2->value<<endl;


}
