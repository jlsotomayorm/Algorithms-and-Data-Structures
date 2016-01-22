#include "Ordenamiento.h"

Ordenamiento::Ordenamiento()
{
    //ctor
}

Ordenamiento::~Ordenamiento()
{
    //dtor
}

void Ordenamiento:: llenar (int tama)
{
    srand((unsigned)time(0));
    int var;
    for (int i = 0; i < tama; i ++)
    {
        var = (rand()%tama)+1;
        datos.push_back (var);
    }
}

void Ordenamiento:: print()
{
    for (int i = 0; i < datos.size(); i ++)
    {
    cout << datos [i] << "-";
    }
}
