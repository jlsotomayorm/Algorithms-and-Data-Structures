#include "ArbolEnhebrado.h"

int main()
{
	ArbolBB arbol;
	arbol.Insertar(1);
	arbol.Insertar(0);
	arbol.Insertar(10);
	arbol.Insertar(5);
	arbol.RecorridoInverso();

	return 0;
}
