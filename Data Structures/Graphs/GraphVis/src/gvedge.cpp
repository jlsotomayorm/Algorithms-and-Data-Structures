#include "gvedge.h"

GVEdge::GVEdge()
{
    //path = new QPainterPath();
}

GVEdge::~GVEdge()
{
//    if(path)
//            delete path;
}
void GVEdge::setSource(QString s)
{
    source =s;
}
void GVEdge::setTarget(QString t)
{
    target =t;
}

void GVEdge::setPath(QPainterPath p)
{
    path=p;
}

QString GVEdge::getSource()
{
    return source;
}
QString GVEdge::getTarget()
{
    return target;
}
QPainterPath GVEdge::getPath()
{
    return path;
}
