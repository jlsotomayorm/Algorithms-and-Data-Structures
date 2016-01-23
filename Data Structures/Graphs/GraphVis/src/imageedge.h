#ifndef IMAGEEDGE_H
#define IMAGEEDGE_H
#include "imagevertex.h"
class ImageEdge
{
private:
        //Distancia a otra imagen
        double dist;
        bool flag;
        //Nodo destino
        ImageVertex  target;


public:
    ImageEdge(ImageVertex &v,double d=1);
    ImageEdge(const ImageVertex &v,double d=1);
    ImageEdge(){}
    bool operator==(const ImageEdge& otro)const;
    void operator=(const ImageEdge& otro);
    bool operator<(const ImageEdge& otro) const;
    bool operator>(const ImageEdge& otro) const;
    ImageVertex getTarget()const ;
    double getDist()const ;
    bool isMarked();
    void setFlag(bool f);
};

#endif // IMAGEEDGE_H
