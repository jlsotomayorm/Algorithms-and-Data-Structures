#ifndef GVNODE_H
#define GVNODE_H
#include <QString>
#include <QPoint>
using namespace std;
class GVNode
{
private:
    //Identificador del nodo
       string name;

       //Punto central del nodo con referencia la esquina superior izquierda
       QPoint centerPos;

       // El tamaño del nodo en pixeles
       double height;
       double width;
public:
    GVNode();

    void setName(string name);
    void setCenter(QPoint pos);
    void setPixelSize(double h,double w);
    void setHeight(double h);
    void setWidth(double w);
    string getName();
    QPoint getCenter();
    double getWidth();
    double getHeight();

    //Esquina superior izquierda
    double getX();
    double getY();

};

#endif // GVNODE_H
