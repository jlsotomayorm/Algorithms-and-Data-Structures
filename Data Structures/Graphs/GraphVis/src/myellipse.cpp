#include "myellipse.h"
#include <iostream>

using namespace std;
MyEllipse::MyEllipse(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent):QGraphicsEllipseItem(x,y,width,height,parent)
{
    w = new QLabel();
    w->resize(256,256);
    w->setWindowFlags(Qt::Tool);

    path="";

}

void MyEllipse::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    cout<<"Showing: "<<path<<endl;
    QImage imagen;
    if (imagen.load(path.c_str()))
        w->setPixmap(QPixmap::fromImage(imagen));
    else
        w->setPixmap(QPixmap::fromImage(QImage("imagen.png")));


    w->show();

}

void MyEllipse::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
  cout<<"Leaving"<<endl;
  w->close();
}

void MyEllipse::setPath(string p)
{
    path = p;
}


