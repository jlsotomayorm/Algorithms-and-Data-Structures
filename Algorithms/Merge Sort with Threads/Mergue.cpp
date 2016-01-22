#include "Mergue.h"

Mergue::Mergue()
{
    //ctor
	n_hilos=0;
	max_hilos=2;
	
}

Mergue::~Mergue()
{
    //dtor
}

void Mergue:: merge_sort(int low,int high)
{
    int mid;
    if(low<high)
    {
    mid=(low+high)/2;

	if(n_hilos<max_hilos)
	{
		//Aumentamos el contador de hilos
		n_hilos++;

		//Declaramos los hilos a utilizar 
			boost::thread hilo1;
			
		//Al momento de la llamada recursiva lanzamos un hilo separado
			hilo1 = boost::thread(&Mergue::merge_sort,this,low,mid);

			merge_sort(mid+1,high);
		//Esperamos a q los dos hilso terminen para recien juntar
			hilo1.join();
	}
	else
	{
		merge_sort(low,mid);
		merge_sort(mid+1,high);
	}
		
	
	//LLamamos a la funcion que junta


	 merge(low,mid,high);
    }
}

void Mergue:: merge(int low,int mid,int high)
{
    int h,i,j,b[datos.size()],k;
    h=low;
    i=low;
    j=mid+1;

    while((h<=mid)&&(j<=high))
    {
    if(datos[h]<=datos[j])
    {
    b[i]=datos[h];
    h++;
    }
    else
    {
    b[i]=datos[j];
    j++;
    }
    i++;
    }
    if(h>mid)
    {
    for(k=j;k<=high;k++)
    {
    b[i]=datos[k];
    i++;
    }
    }
    else
    {
    for(k=h;k<=mid;k++)
    {
    b[i]=datos[k];
    i++;
    }
    }
    for(k=low;k<=high;k++)
    datos[k]=b[k];
}

void Mergue:: ordena ()
{
    cout << "Mergue " << datos.size () << ":";
    merge_sort (0,datos.size()-1);
}

void Mergue::setNHilos(int n)
{
	max_hilos=n;
}


