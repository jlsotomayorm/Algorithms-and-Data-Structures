#include <iostream>
#include "Mergue.h"

int main()
{

	Mergue m;
	clock_t t_ini, t_fin;
        double secs;

	m.setNHilos(3);

	m.llenar(1900000);
	cout<<"Sin ordenar"<<endl;
	//m.print();

	t_ini = clock();
	m.ordena();
	
	t_fin = clock();
	cout<<"Termino de Ordenar"<<endl;

     secs = (float)(t_fin - t_ini) / CLOCKS_PER_SEC;
     cout<<secs<<endl;
	
	//m.print();

	 

	cout<<endl;

	return 0;
}
