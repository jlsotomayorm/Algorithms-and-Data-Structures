#ifndef MYELLIPSE_H
#define MYELLIPSE_H
#include<QGraphicsEllipseItem>
#include <Qt>
#include <QLabel>
#include <string>
using namespace std;
class MyEllipse : public QGraphicsEllipseItem
{
private:
        QLabel *w;
        string path;
public:
    MyEllipse(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void setPath(string p);
};

#endif // MYELLIPSE_H
