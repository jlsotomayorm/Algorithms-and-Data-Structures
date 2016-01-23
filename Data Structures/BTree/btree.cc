#include "btree.h"
#include <stddef.h>

Btree::Btree(int m){
  this->m = m;
  root = NULL;
}
Btree::~Btree(){
 
}
bool Btree::search(int key){
  Node *tmp = search(key, root);
  if(tmp) return tmp->hasKey(key); 
  return false;
}
Node* Btree::search(int key, Node *node){
  if(node == NULL) return node;

  Node *next = node->search(key);
  if(next == node) return node;
  return search(key, next);
}
bool Btree::insert(int key){
  Node *n = search(key, root);
  if(n->hasKey(key)) return true;

  n->insert(key,NULL);
  
  if(n->isFull())
    return n->split();
  
  return true;
}

