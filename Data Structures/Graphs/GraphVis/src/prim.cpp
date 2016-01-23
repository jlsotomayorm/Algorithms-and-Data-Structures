#include "prim.h"
#include <queue>
using namespace std;
Prim::Prim()
{
}

void Prim::visit(Graph *g, Graph *r)
{
    map<ImageVertex,list<ImageEdge> > graph = g->getDataStructure();
    map<ImageVertex,list<ImageEdge> >::iterator it = graph.begin();

    priority_queue<ImageEdge,vector<ImageEdge>,greater<ImageEdge> > cola;

    map<ImageVertex,bool>visited;
    map<ImageEdge,ImageVertex> from;
    int nVertex = g->getNVertex();

    //Agregamos el primer nodo al MST
    r->addVertex(it->first);
    visited[it->first]=true;
    //Agregamos todas sus aristas a la cola de prioridad
    list<ImageEdge>::iterator ini = it->second.begin();
    list<ImageEdge>::iterator fin = it->second.end();


        for(;ini!=fin;ini++)
        {

            cola.push(*ini);
            //Comparacion completa con target y dist
            ini->setFlag(true);
            from[*ini]= it->first;
        }

        ImageVertex actual = it->first;

        while(nVertex!=visited.size())
        {

            ImageEdge minEdge = cola.top();
            actual = from[minEdge];
            ImageVertex target = minEdge.getTarget();
            cola.pop();
            if(visited.find(actual)!=visited.end() && visited.find(target)==visited.end())
            {
                r->addVertex(actual);
                r->addVertex(target);
                r->addEdge(actual,target,minEdge.getDist());

                //Visitamos
                visited[target]=true;

                list<ImageEdge>::iterator ini2 = graph[target].begin();
                list<ImageEdge>::iterator fin2 = graph[target].end();

                for(;ini2!=fin2;ini2++)
                {
                    if(visited.find(ini2->getTarget())==visited.end())
                    {
                        cola.push(*ini2);
                        //Comparacion completa con target y dist
                        ini2->setFlag(true);
                        from[*ini2]= target;
                    }
                }
            }


        }




}
