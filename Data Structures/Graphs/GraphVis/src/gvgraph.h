#ifndef GVGRAPH_H
#define GVGRAPH_H
//#include <graphviz/cgraph.h>
#include <Qt>
#include <QMap>
#include <QFont>
#include <graphviz/gvc.h>
//#include <graphviz/gvplugin_render.h>
#include <graphviz/graph.h>
#include <QPair>
#include "Auxiliar.h"
#include <QStringList>
#include <string>
#include <QString>
#include <QRectF>
#include "gvnode.h"
#include <sstream>
#include "gvedge.h"
using namespace std;
class GVGraph
{
    static const qreal DotDefaultDPI;
public:
    GVGraph(string name, QFont font=QFont(), qreal node_size=50);
    ~GVGraph();

    // Agregar y eliminar nodos
    void addNode(string name);
    void addNodes(const QStringList& names);
    void removeNode(string name);
    void clearNodes();

    // Agregar y eliminar aristas
      void addEdge(string source, string target);
      void addEdge(string source,string target,double length);
      void removeEdge(string source, string target);
      void removeEdge(const QPair<string, string> &key);

      // Setear la fuente de las etiquetas
      void setFont(QFont font);

      //Seteamos la raiz
      void setRootNode(string name);

      //Aplicamos layout
      void applyLayout();

      //En un archivo
      void renderToFile(const char* name);

      //Graficar en pantalla
      QRectF boundingRect() const;
      QList<GVNode> nodes() const;
      QList<GVEdge> edges() const;
private:
    GVC_t *_context;
    Agraph_t *_graph;
    QFont _font;
    QMap<string, Agnode_t*> _nodes;
    QMap<QPair<string, string>, Agedge_t*> _edges;
};

#endif // GVGRAPH_H
