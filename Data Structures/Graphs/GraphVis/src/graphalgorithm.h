#ifndef GRAPHALGORITHM_H
#define GRAPHALGORITHM_H
#include "graph.h"
class GraphAlgorithm
{
public:
    GraphAlgorithm();
    virtual void visit(Graph * g,Graph * r=0)=0;
};

#endif // GRAPHALGORITHM_H
