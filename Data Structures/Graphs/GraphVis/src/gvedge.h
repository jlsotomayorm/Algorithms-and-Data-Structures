#ifndef GVEDGE_H
#define GVEDGE_H
#include <QPainterPath>
class GVEdge
{
private:
    // Nodos destino y fuente
      QString source;
      QString target;

     // Path de la arista - linea

public:
    GVEdge();
    ~GVEdge();

    void setSource(QString s);
    void setTarget(QString t);
    void setPath(QPainterPath p);

    QString getSource();
    QString getTarget();
    QPainterPath getPath();

    QPainterPath path;
};

#endif // GVEDGE_H
