#ifndef KRUSKAL_H
#define KRUSKAL_H
#include "graphalgorithm.h"

class Kruskal: public GraphAlgorithm
{
 private:
    map<pair<ImageVertex,ImageVertex>,bool> noPairs;
    list<map<ImageVertex,bool> > bosque;

    list<pair<int,pair<ImageVertex,ImageVertex> > >  aristas;
    int * raices;
public:
    Kruskal();
    ~Kruskal();
    void visit(Graph *g,Graph *r=0);
    int findSet(int a);
};

#endif // KRUSKAL_H
