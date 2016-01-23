#include "imageedge.h"

ImageEdge::ImageEdge(ImageVertex &v, double d)
{
    target =v;
    dist = d;
    flag = false;

}

ImageEdge::ImageEdge(const ImageVertex &v, double d)
{
    target =v;
    dist = d;


}

bool ImageEdge:: operator==(const ImageEdge& otro)const
{
    if(flag)
            return dist==otro.dist && target==otro.target;

    //Comparamos arista solo por nodo destino
    if(/*dist==otro.dist&&*/ target==otro.target )
            return true;

    return false;
}

bool ImageEdge::operator<(const ImageEdge& otro) const
{

    return dist<otro.dist;
}

bool ImageEdge::operator>(const ImageEdge& otro) const
{

    return dist>otro.dist;
}

void ImageEdge::operator =(const ImageEdge &otro)
{
    target = otro.target;
    dist = otro.dist;
}

ImageVertex ImageEdge::getTarget() const
{
    return target;
}

double ImageEdge::getDist()const
{
    return dist;
}

void ImageEdge::setFlag(bool f)
{
    flag = f;
}


