#ifndef BTREE_H
#define BTREE_H

#include "node.h"

class Btree{
  private:
    int m;
    Node* root;
    Node* search(int, Node*);
  public:
    Btree(int m);
    virtual ~Btree();
    bool search(int key);
    bool insert(int key);
};
#endif
