#ifndef NODE_H
#define NODE_H
#include <vector>

using namespace std;
class Btree;
class Node{
  private:
    vector<int> keys;
    vector<Node*> children;
    Node* parent;
    int m;
  public:
    Node(int m);
    virtual ~Node();
    bool hasKey(int key);
    bool isFull();
    bool split();
    Node* search(int key);
    void insert(int key, Node *son);
    int getMedian();
    vector<int> removeKeysGreaterThanMedian();
    vector<Node*> removeChildrenGreaterThanMedian();

    void setParent(Node* parent);
    Node* getParent();

    void setKeys(vector<int>  keys);
    void setSons(vector<Node*>  sons);

};
#endif
