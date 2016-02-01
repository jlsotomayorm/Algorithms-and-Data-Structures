#ifndef GRAFO_H
#define GRAFO_H
#include <map>
#include <vector>
#include <utility>
#include <limits>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;


class Grafo
{
private:

    map<int,vector<pair<int,int> > > graph;
public:
    Grafo();
    void insertEdge(int nodoS,int nodoD,int peso);
    void dijkstra(int source,map<int,int> &d,map<int,int> &d2,int total);
};

#endif // GRAFO_H
