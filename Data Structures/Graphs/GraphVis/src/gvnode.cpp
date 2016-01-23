#include "gvnode.h"

GVNode::GVNode()
{
}
void GVNode:: setName(string n)
{
    name=n;
}
void GVNode::setCenter(QPoint pos)
{
    centerPos=pos;
}
void GVNode::setPixelSize(double h,double w)
{
    height=h;
    width=w;
}

void GVNode::setHeight(double h)
{
    height=h;
}
void GVNode::setWidth(double w)
{
    width=w;
}
string GVNode::getName()
{
    return name;
}
QPoint GVNode:: getCenter()
{
    return centerPos;
}

double GVNode::getWidth()
{
    return width;
}
double GVNode::getHeight()
{
    return height;
}

double GVNode::getX()
{
    double x = centerPos.x();
    //Damos esquina superior izquierda
    return x-width/2;
}

double GVNode::getY()
{
    double y= centerPos.y();
    //Damos esquina superior izquierda
    return y-height/2;
}
