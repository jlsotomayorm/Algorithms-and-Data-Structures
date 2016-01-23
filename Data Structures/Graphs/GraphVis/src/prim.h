#ifndef PRIM_H
#define PRIM_H
#include "graphalgorithm.h"
class Prim : public GraphAlgorithm
{
public:
    Prim();
    ~Prim();
     void visit(Graph *g,Graph *r=0);
};

#endif // PRIM_H
