#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include "gvgraph.h"
#include <list>
#include <algorithm>
#include "imageedge.h"
#include "imagevertex.h"
#include <sstream>
#include <QGraphicsScene>
using namespace std;

class GraphAlgorithm;
class Graph
{

private:
        map<ImageVertex,list<ImageEdge> > mygraph;
        GVGraph *gv_graph;
        int nVertex;
        int nEdges;
        //Relacion entre Grafo y  GVGraph
        map<ImageVertex,string> indices;
        map <string,ImageVertex> relacion;
         Graph * mst;
public:
    Graph();
    ~Graph();
    void addVertex(ImageVertex &vertex);
    void addVertex(const ImageVertex &vertex);

    void addEdge(ImageVertex &source,ImageVertex &target,double dist=1 );
    void addEdge(const ImageVertex &source,const ImageVertex &target,double dist=1 );

    void eraseVertex(ImageVertex & vertex);
    void eraseEdge(ImageVertex &source,ImageVertex &target);

    void qtRender(QGraphicsScene *sc);
    void qtRenderMST(QGraphicsScene *sc);
    void accept(GraphAlgorithm * al);
    //Usado por los visitantes
     map<ImageVertex,list<ImageEdge> > getDataStructure();

    bool isEmpty();
    int getNVertex();

};

#endif // GRAPH_H
