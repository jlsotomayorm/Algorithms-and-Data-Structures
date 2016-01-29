#include "segmento.h"

const int HEIGHT = 511;
bool puntoInterseccions(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int &rx, int &ry)
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
Segmento::Segmento(int x1, int y1, int x2, int y2)
{
    if(x1<x2)
    {
        inicio.first = x1;
        inicio.second = y1;

        fin.first = x2;
        fin.second = y2;
    }
    else
    {
        inicio.first = x2;
         inicio.second = y2;
         fin.first = x1;
         fin.second = y1;
    }

    b=NULL;


}

Segmento::Segmento(const Segmento &otro)
{

    inicio.first = otro.inicio.first;
    inicio.second = otro.inicio.second;

    fin.first = otro.fin.first;
    fin.second = otro.fin.second;

    b = otro.b;

    enlinea.first = otro.enlinea.first;
    enlinea.second = otro.enlinea.second;
}

Segmento::~Segmento()
{


}


bool Segmento::operator <(const Segmento & otro)const
{
 /*   if(enlinea.second==otro.enlinea.second)
        return enlinea.first<otro.enlinea.first;
    else
        return enlinea.second<otro.enlinea.second;

        */

    int interX,interY;
    puntoInterseccions(otro.inicio.first,otro.inicio.second,otro.fin.first,otro.fin.second,enlinea.first+1,0,enlinea.first+1,HEIGHT,interX,interY);


    if(interY==enlinea.second)
           return enlinea.first<interX;
       else
           return enlinea.second<interY;


}

bool Segmento::operator ==(const Segmento & otro)const
{
    return inicio.first==otro.inicio.first && inicio.second==otro.inicio.second && fin.first==otro.fin.first && fin.second==otro.fin.second /*&& enlinea.first ==otro.enlinea.first && enlinea.second ==otro.enlinea.second*/;
}
bool  Segmento::operator !=(const Segmento & otro)const
{
 return inicio.first!=otro.inicio.first && inicio.second!=otro.inicio.second && fin.first!=otro.fin.first && fin.second!=otro.fin.second;
}
bool  Segmento::operator >(const Segmento & otro)const
{
   /* if(enlinea.second==otro.enlinea.second)
        return enlinea.first>otro.enlinea.first;
    else
        return enlinea.second>otro.enlinea.second;*/

    int interX,interY;
    puntoInterseccions(otro.inicio.first,otro.inicio.second,otro.fin.first,otro.fin.second,enlinea.first+1,0,enlinea.first+1,HEIGHT,interX,interY);


    if(interY==enlinea.second)
           return enlinea.first>interX;
       else
           return enlinea.second>interY;
}

bool Segmento::esIzquierdo(pair<int, int> uno)
{
    return inicio==uno;
}

bool Segmento::esDerecho(pair<int, int> uno)
{
    return fin==uno;
}

bool Segmento::isBelow(Segmento &otro)
{
    return inicio.second<otro.inicio.second;
}

int Segmento::getX1()
{
    return inicio.first;
}

int Segmento::getY1()
{
    return inicio.second;
}
int Segmento::getX2()
{
    return fin.first;
}
int Segmento::getY2()
{
    return fin.second;
}

void Segmento::relacionarSegmento(Segmento * r)
{
    b = r;
}
Segmento * Segmento::getSegmentoRelacionado()
{
    return b;
}

void Segmento::setPuntoEnLinea(pair<int,int> & punto)
{
    enlinea = punto;
}
void Segmento::setPuntoEnLinea(int x,int y)
{
    enlinea.first = x;
    enlinea.second = y;
}

void Segmento::printActualPoint()
{
    cout<<enlinea.first<<" "<<enlinea.second<<endl;
}

void Segmento::printPoints()
{
    cout<<inicio.first<<" "<<inicio.second<<endl;
    cout<<fin.first<<" "<<fin.second<<endl;
}

ostream& operator<<(ostream & os,Segmento &otro)
{
    os<<otro.inicio.second;
    return os;

}
