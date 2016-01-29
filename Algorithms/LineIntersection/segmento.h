#ifndef SEGMENTO_H
#define SEGMENTO_H
#include <utility>
#include <iostream>

using namespace std;
class Segmento
{
private:

        pair <int,int> inicio;
        pair <int,int> fin;

        pair <int,int> enlinea;
        //Segmento relacionado
        Segmento * b;



public:
    Segmento(int x1,int y1, int x2,int y2);
    Segmento(){};
    Segmento(const Segmento & otro);
    ~Segmento();


    bool operator <(const Segmento & otro)const;
    bool operator ==(const Segmento & otro)const;
    bool operator !=(const Segmento & otro)const;
    bool operator >(const Segmento & otro)const;
    friend ostream& operator<<(ostream & os,Segmento &otro);

    bool isBelow(Segmento &otro);

    bool esIzquierdo(pair<int,int> uno);
    bool esDerecho(pair<int,int> uno);

    void setPuntoEnLinea(pair<int,int> & punto);
    void setPuntoEnLinea(int x,int y);

    int getX1();
    int getY1();
    int getX2();
    int getY2();

    void relacionarSegmento(Segmento * r);
    Segmento * getSegmentoRelacionado();

    void printActualPoint();
    void printPoints();

};

#endif // SEGMENTO_H
