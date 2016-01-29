#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <algorithm>
#include "segmento.h"
int dotproduct(int x0,int y0,int x1,int y1,int x2,int y2)
{
    return  (x1-x0)*(y2-y0) -(x2-x0)*(y1-y0);

}

bool enSegmento(int x0,int y0,int x1,int y1,int x2,int y2)
{

    if(min(x0,x1)<= x2 && x2 <= max(x0,x1) && min(y0,y1)<= y2 && y2 <= max(y0,y1))
            return true;

    return false;
}


bool interseccionSegmentos(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
{
    int d1,d2,d3,d4;

    d1 = dotproduct(x3,y3,x4,y4,x1,y1);
    d2 = dotproduct(x3,y3,x4,y4,x2,y2);
    d3 = dotproduct(x1,y1,x2,y2,x3,y3);
    d4 = dotproduct(x1,y1,x2,y2,x4,y4);

    if( ((d1>0 && d2 <0) || (d1<0 &&d2>0)) && ((d3>0 && d4<0) || (d4>0 && d3<0)))
    {
        return true;
    }

    if(d1==0 && enSegmento(x3,y3,x4,y4,x1,y1)) return true;
    if(d2==0 && enSegmento(x3,y3,x4,y4,x2,y2)) return true;
    if(d3==0 && enSegmento(x1,y1,x2,y2,x3,y3)) return true;
    if(d4==0 && enSegmento(x1,y1,x2,y2,x4,y4)) return true;

    return false;

}

bool puntoInterseccion(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,int & rx,int &ry)
{

    int d = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);

    if (d == 0) return false;

   int xi = ((x3-x4)*(x1*y2-y1*x2)-(x1-x2)*(x3*y4-y3*x4))/d;
   int yi = ((y3-y4)*(x1*y2-y1*x2)-(y1-y2)*(x3*y4-y3*x4))/d;


   if (xi < min(x1,x2) || xi > max(x1,x2)) return false;
   if (xi < min(x3,x4) || xi > max(x3,x4)) return false;

    rx = xi;
    ry = yi;
   return true;
}

bool interseccionSegmentos(Segmento a,Segmento b,pair<int,int> & rpta)
{
     int x,y;
    if(puntoInterseccion(a.getX1(),a.getY1(),a.getX2(),a.getY2(),b.getX1(),b.getY1(),b.getX2(),b.getY2(),x,y))
    {
        rpta = make_pair(x,y);
        return true;
    }

    return false;
}






#endif // FUNCIONES_H
