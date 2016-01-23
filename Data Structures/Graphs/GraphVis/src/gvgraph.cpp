#include "gvgraph.h"

const qreal GVGraph::DotDefaultDPI=72.0;

GVGraph::GVGraph(string name,QFont font ,qreal node_size): _context(gvContext()),
    _graph(_agopen(name, AGDIGRAPHSTRICT))
{


    //Seteamos los atributos del grafo
        _agset(_graph, "overlap", "prism");
       _agset(_graph, "splines", "true");
       _agset(_graph, "pad", "0.2");
       _agset(_graph, "dpi", "96.0");
       _agset(_graph, "nodesep", "0.4");


       //Seteamos los atributos de los nodos
           _agnodeattr(_graph, "fixedsize", "true");
           _agnodeattr(_graph, "label", "");
           _agnodeattr(_graph, "regular", "true");


        //Dividimos el ancho deseado entre DPI para obtener el valor en puntos
           double rpta = node_size/_agget(_graph, "dpi", "96.0").toDouble();

           stringstream ss;
           ss<<rpta;

           //GV uses , instead of . for the separator in floats
           _agnodeattr(_graph, "width", ss.str()/*.replace('.', ",")*/);

           setFont(font);


}

GVGraph::~GVGraph()
{
    gvFreeLayout(_context, _graph);
    agclose(_graph);
    gvFreeContext(_context);
}

void GVGraph::addNode(string name)
{
    if(_nodes.contains(name))
        removeNode(name);

    _nodes.insert(name, _agnode(_graph, name));

}


void GVGraph::addNodes(const QStringList& names)
{
    for(int i=0; i<names.size(); ++i)
        addNode(names.at(i).toStdString());
}


void GVGraph::removeNode(string name)
{
    if(_nodes.contains(name))
    {
        agdelete(_graph, _nodes[name]);
        _nodes.remove(name);

        QList<QPair<string, string> >keys=_edges.keys();
        for(int i=0; i<keys.size(); ++i)
            if(keys.at(i).first==name || keys.at(i).second==name)
                removeEdge(keys.at(i));
    }
}

void GVGraph::clearNodes()
{
    QList<string> keys=_nodes.keys();

    for(int i=0; i<keys.size(); ++i)
        removeNode(keys.at(i));
}
void GVGraph::setRootNode(string name)
{
    if(_nodes.contains(name))
        _agset(_graph, "root", name);
}

void GVGraph::addEdge(string source, string target)
{
    if(_nodes.contains(source) && _nodes.contains(target))
    {

        QPair<string, string> key(source, target);
        if(!_edges.contains(key))
        {
            // cout<<"Inserting edge"<<endl;
            _edges.insert(key, agedge(_graph, _nodes[source], _nodes[target]));

        }
    }
}

void GVGraph::addEdge(string source, string target, double length)
{
    if(_nodes.contains(source) && _nodes.contains(target))
    {

        QPair<string, string> key(source, target);
        if(!_edges.contains(key))
        {
            // cout<<"Inserting edge"<<endl;

            stringstream ss;
            ss<<length;
            Agedge_t * arista = agedge(_graph, _nodes[source], _nodes[target]);
            _agset(arista,"len",ss.str());
            _edges.insert(key,arista );

        }
    }

}


void GVGraph::removeEdge(string source, string target)
{
    removeEdge(QPair<string, string>(source, target));
}

void GVGraph::removeEdge(const QPair<string, string>& key)
{
    if(_edges.contains(key))
    {
        //agdelete(_graph, _edges[key].first);
        agdelete(_graph, _edges[key]);
        _edges.remove(key);
    }
}

void GVGraph::setFont(QFont font)
{
    _font=font;

    _agset(_graph, "fontname", font.family().toStdString());
    _agset(_graph, "fontsize", QString("%1").arg(font.pointSizeF()).toStdString());

    _agnodeattr(_graph, "fontname", font.family().toStdString());
    _agnodeattr(_graph, "fontsize", QString("%1").arg(font.pointSizeF()).toStdString());

    _agedgeattr(_graph, "fontname", font.family().toStdString());
    _agedgeattr(_graph, "fontsize", QString("%1").arg(font.pointSizeF()).toStdString());

}

void GVGraph::applyLayout()
{
    gvFreeLayout(_context, _graph);
    cout<<"Aplicando Layout"<<endl;
    gvLayout(_context, _graph, "neato");


}
void GVGraph::renderToFile(const char* name)
{
    applyLayout();
    gvRenderFilename(_context,_graph,"png",name);

}

QRectF GVGraph::boundingRect() const
{
    qreal dpi=_agget(_graph, "dpi", "96.0").toDouble();
        return QRectF(_graph->u.bb.LL.x*(dpi/DotDefaultDPI), _graph->u.bb.LL.y*(dpi/DotDefaultDPI),
                      _graph->u.bb.UR.x*(dpi/DotDefaultDPI), _graph->u.bb.UR.y*(dpi/DotDefaultDPI));
}

QList<GVNode> GVGraph::nodes() const
{

    QList<GVNode> list;
    qreal dpi=_agget(_graph, "dpi", "96.0").toDouble();

    for(QMap<string, Agnode_t*>::const_iterator it=_nodes.begin(); it!=_nodes.end();++it)
    {
        Agnode_t *node=it.value();
        GVNode object;


        object.setName(node->name);

        //Obtenemos la coordenada X , aplicando conversion de DPI.

        qreal x=node->u.coord.x*(dpi/DotDefaultDPI);

        //Convertimos las coordenadas Y de abajo-izquierda -> arriba izquierda
        qreal y=(_graph->u.bb.UR.y - node->u.coord.y)*(dpi/DotDefaultDPI);
        object.setCenter(QPoint(x, y));


        //Convertimos widh y height de pulgadas a pixeles
        object.setHeight(node->u.height*dpi);
        object.setWidth(node->u.width*dpi);

        list << object;
    }

    return list;
}

QList<GVEdge> GVGraph::edges() const
{

   QList<GVEdge> list;

    qreal dpi=_agget(_graph, "dpi", "96.0").toDouble();

    for(QMap<QPair<string, string>, Agedge_t* >::const_iterator it=_edges.begin();
        it!=_edges.end();++it)
    {
        Agedge_t *edge=it.value();
        GVEdge object;

        //LLenamos los nombres de los nodos que une la arista
        object.setSource(edge->tail->name);
        object.setTarget(edge->head->name);


        //Calculamos el camino de acuerdo a las lineas del grafo.

        if((edge->u.spl->list!=0) && (edge->u.spl->list->size%3 == 1))
        {
            //If there is a starting point, draw a line from it to the first curve point
            if(edge->u.spl->list->sflag)
            {
                object.path.moveTo(edge->u.spl->list->sp.x*(dpi/DotDefaultDPI),
                             (_graph->u.bb.UR.y - edge->u.spl->list->sp.y)*(dpi/DotDefaultDPI));
                object.path.lineTo(edge->u.spl->list->list[0].x*(dpi/DotDefaultDPI),
                        (_graph->u.bb.UR.y - edge->u.spl->list->list[0].y)*(dpi/DotDefaultDPI));
            }
            else
                object.path.moveTo(edge->u.spl->list->list[0].x*(dpi/DotDefaultDPI),
                        (_graph->u.bb.UR.y - edge->u.spl->list->list[0].y)*(dpi/DotDefaultDPI));


            //Accedemos a los puntos de curva

            for(int i=1; i<edge->u.spl->list->size; i+=3)
                object.path.cubicTo(edge->u.spl->list->list[i].x*(dpi/DotDefaultDPI),
                      (_graph->u.bb.UR.y - edge->u.spl->list->list[i].y)*(dpi/DotDefaultDPI),
                      edge->u.spl->list->list[i+1].x*(dpi/DotDefaultDPI),
                      (_graph->u.bb.UR.y - edge->u.spl->list->list[i+1].y)*(dpi/DotDefaultDPI),
                      edge->u.spl->list->list[i+2].x*(dpi/DotDefaultDPI),
                      (_graph->u.bb.UR.y - edge->u.spl->list->list[i+2].y)*(dpi/DotDefaultDPI));


            //Si hay un punto de destino, dibujamos una linea hacia el.
            if(edge->u.spl->list->eflag)
                object.path.lineTo(edge->u.spl->list->ep.x*(dpi/DotDefaultDPI),
                             (_graph->u.bb.UR.y - edge->u.spl->list->ep.y)*(dpi/DotDefaultDPI));
        }

        list << object;
    }

    return list;
}





