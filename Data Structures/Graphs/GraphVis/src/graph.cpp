#include "graph.h"
#include "myellipse.h"
#include "graphalgorithm.h"

Graph::Graph()
{
    gv_graph= new GVGraph("Relacion");
    nVertex=0;
    nEdges=0;
    mst=0;
}

Graph::~Graph()
{
    if(gv_graph)
            delete gv_graph;
    if(mst)
            delete mst;

}
void Graph::addVertex(ImageVertex& vertex)
{
    //Insertamos el vertice con una lista por defecto vacia

    if(mygraph.find(vertex)==mygraph.end())
    {
        mygraph[vertex];
        nVertex++;

        stringstream ss;
        ss<<nVertex;
        string id = ss.str();

        //LLevamos la relación entre Graph y GVGraph
        indices[vertex]=id;
        relacion[id]=vertex;

        //Añadimos al grafo para dibujar
        gv_graph->addNode(id);

    }
}

void Graph::addVertex(const ImageVertex& vertex)
{
    //Insertamos el vertice con una lista por defecto vacia

    if(mygraph.find(vertex)==mygraph.end())
    {
        mygraph[vertex];
        nVertex++;

        stringstream ss;
        ss<<nVertex;
        string id = ss.str();

        //LLevamos la relación entre Graph y GVGraph
        indices[vertex]=id;
        relacion[id]=vertex;

        //Añadimos al grafo para dibujar
        gv_graph->addNode(id);

    }
}
void Graph::addEdge(ImageVertex &source,ImageVertex& target,double dist )
{
    //Solo inserta la arista si existen los nodos
    if(mygraph.find(source)!=mygraph.end() && mygraph.find(target)!=mygraph.end())
    {
        //Si no existe la arista la inserta
        ImageEdge arista(target,dist);
        if(find(mygraph[source].begin(),mygraph[source].end(),arista)==mygraph[source].end())
        {
            nEdges++;
            mygraph[source].push_back(arista);
            //Como es un grafo no dirigido insertamos la otra relacion
            ImageEdge arista2(source,dist);
            mygraph[target].push_back(arista2);

            //Agregar peso de la arista si se desea graficar por Distancias
            gv_graph->addEdge(indices[source],indices[target],dist/5);
        }


    }

}

void Graph::addEdge(const ImageVertex &source,const ImageVertex& target,double dist )
{
    //Solo inserta la arista si existen los nodos
    if(mygraph.find(source)!=mygraph.end() && mygraph.find(target)!=mygraph.end())
    {
        //Si no existe la arista la inserta
        ImageEdge arista(target,dist);
        if(find(mygraph[source].begin(),mygraph[source].end(),arista)==mygraph[source].end())
        {
            nEdges++;
            mygraph[source].push_back(arista);
            //Como es un grafo no dirigido insertamos la otra relacion
            ImageEdge arista2(source,dist);
            mygraph[target].push_back(arista2);

            //Agregar peso de la arista si se desea graficar por Distancias
            gv_graph->addEdge(indices[source],indices[target],dist/5);
        }


    }

}
void Graph::eraseVertex(ImageVertex &vertex)
{
    map<ImageVertex,list<ImageEdge> >::iterator it ;
    it = mygraph.find(vertex);
    if(it!=mygraph.end())
    {
        mygraph.erase(it);
        nVertex--;
        for(it=mygraph.begin();it!=mygraph.end();it++)
        {

            list<ImageEdge> *l = &(it->second);
            list<ImageEdge>::iterator it2;
            ImageEdge arista(vertex);
            it2=find(l->begin(),l->end(),arista);
            if(it2!=l->end())
            {
                l->erase(it2);
            }
            cout<<"Arista asociada al nodo elminada"<<endl;
        }

        gv_graph->removeNode(indices[vertex]);
    }

}
void Graph::eraseEdge(ImageVertex &source, ImageVertex &target)
{

   //Buscamos si existen los nodos involucrados
    if(mygraph.find(source)!=mygraph.end() && mygraph.find(target)!=mygraph.end())
    {
        //Buscamos si existe la arista
        ImageEdge arista(target);
       list<ImageEdge> ::iterator it =find(mygraph[source].begin(),mygraph[source].end(),arista);
        if(it!=mygraph[source].end())
        {
            //Eliminamos la arista del nodo origen
            mygraph[source].erase(it);
            //Eliminamos la arista del nodo destino
            list<ImageEdge> ::iterator it2 =find(mygraph[target].begin(),mygraph[target].end(),arista);
            mygraph[target].erase(it2);

            QPair<string,string> par(indices[source],indices[target]);
            gv_graph->removeEdge(par);

            nEdges--;
        }

    }
}

void Graph::qtRender(QGraphicsScene *sc)
{
    gv_graph->applyLayout();
    cout<<"Finishing Layout"<<endl;
    QList<GVNode> nodos = gv_graph->nodes();
    QList<GVEdge> aristas = gv_graph->edges();

    sc->setSceneRect(gv_graph->boundingRect());

    cout<<"Adding Nodes! "<<endl;
    for(QList<GVNode>::iterator it = nodos.begin();it!=nodos.end();it++)
    {

        GVNode tmp =*it;
        string nombre =tmp.getName();
        cout<<"Adding element: "<<nombre<<endl;
        MyEllipse *elipse =new MyEllipse(tmp.getX(),tmp.getY(),tmp.getWidth(),tmp.getHeight());
        elipse->setAcceptHoverEvents(true);
        elipse->setPath(relacion[nombre].getPath());

        elipse->setBrush(QBrush(Qt::lightGray));

        QPen pen;

        pen.setCapStyle(Qt::RoundCap);
        pen.setStyle(Qt::SolidLine);
        pen.setBrush(Qt::blue);
        pen.setWidth(2);


        elipse->setPen(pen);

        sc->addItem(elipse);
    }
    cout<<"Finished Adding nodes!"<<endl;
    cout<<"Adding Edges"<<endl;
    for(QList<GVEdge>::iterator it=aristas.begin();it!=aristas.end();it++)
    {
        cout<<"Adding edge"<<endl;
        GVEdge tmp = *it;

        QGraphicsPathItem * ruta = new QGraphicsPathItem(tmp.getPath());
          QPen pen;
          pen.setCapStyle(Qt::RoundCap);
          pen.setColor(Qt::blue);
         ruta->setPen(pen);
        sc->addItem(ruta);

    }
    cout<<"Finished adding edges"<<endl;

}

map<ImageVertex,list<ImageEdge> > Graph::getDataStructure()
{
    return mygraph;
}

bool Graph::isEmpty()
{
    return nVertex==0;
}

int Graph::getNVertex()
{
    return nVertex;
}

void Graph::accept(GraphAlgorithm *al)
{
    mst = new Graph();

    al->visit(this,mst);
}

void Graph::qtRenderMST(QGraphicsScene *sc)
{
    if(!mst->isEmpty())
        mst->qtRender(sc);
    else
    {
        cout<<"Generate a MST first"<<endl;
    }
}
