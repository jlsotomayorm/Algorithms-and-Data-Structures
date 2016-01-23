#include <vector>
#include <iterator>
#include "node.h"

using namespace std;

Node::Node(int m){
  this->m = m;
}

Node::~Node(){

}

Node *Node::search(int key){
  for(int i = 0; i < keys.size(); i++){
    if(key == keys[i]) return this;
    if(key < keys[i]) 
      if(children[i])
        return children[i]->search(key);
  }
  return NULL;
}
bool Node::hasKey(int key){
  //TODO Research the API for an "in" function
  for(int i = 0; i < keys.size(); i++)
    if(key == keys[i]) return true;
  return false;
}
void Node::insert(int key, Node *son){
  keys.push_back(key);
  children.push_back(son);

  //insert a child in ordered list
  int j = keys.size()-1;
  while(j > 0 && keys[j-1] > keys[j]){
    swap(keys[j],keys[j-1]);
    swap(children[j],children[j-1]);
    j--;
  }
}

int Node::getMedian(){
  return keys[keys.size()/2];
}

vector<int> Node::removeKeysGreaterThanMedian(){
  vector<int> n(make_move_iterator(keys.begin()+keys.size()/2 + 1),
                make_move_iterator(keys.end()));
  keys.erase(keys.begin() + keys.size()/2, keys.end());
  return n;
}

vector<Node*> Node::removeChildrenGreaterThanMedian(){
  vector<Node*> n(make_move_iterator(children.begin()+children.size()/2 + 1),
                make_move_iterator(children.end()));
  children.erase(children.begin()+keys.size()/2+1, children.end());
  return n;
}

bool Node::isFull(){
    return true;
}

bool Node::split(){
  int median = getMedian();
  Node *tmp  = new Node(this->m);
  tmp->setParent(getParent());
  tmp->setKeys(removeKeysGreaterThanMedian());
  tmp->setSons(removeChildrenGreaterThanMedian());
  if(parent)
    parent->insert(median, tmp);
  else{
       Node* newRoot = new Node(this->m);
       setParent(newRoot);
  }
 
}

void Node::setParent(Node* parent){
  this->parent = parent;
}

Node* Node::getParent(){
  return this->parent;
}

void Node::setKeys(vector<int> keys){
  this->keys = keys;
}

void Node::setSons(vector<Node*> sons){
  this->children = sons;
}

