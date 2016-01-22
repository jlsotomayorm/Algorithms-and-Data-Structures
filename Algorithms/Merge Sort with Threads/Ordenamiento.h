#ifndef ORDENAMIENTO_H
#define ORDENAMIENTO_H
#include <vector>
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <time.h>
#include <cstdlib>

using namespace std;

class Ordenamiento
{

    public:
        vector <int> datos;
        Ordenamiento();
        void llenar (int tama);
        void print ();
        virtual void ordena()=0;
        virtual ~Ordenamiento();
    protected:

};











#endif // ORDENAMIENTO_H
