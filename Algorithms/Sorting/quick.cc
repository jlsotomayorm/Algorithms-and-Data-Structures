#include "quick.h"

Quick::Quick(int n):Sort(n)
{
	
}

Quick::~Quick()
{
	delete[] pVector;

}



 void Quick::execute()
{
	clock_t begin = clock();
	quickSort(0,size-1);
	clock_t end = clock();
	
	tiempo = (double) (end-begin) /CLOCKS_PER_SEC;
	
}

void* Quick::ordena(void *p)
{
	
	((Sort*)p)->execute();
	//cout<<"Ordenado con Quick Sort"<<endl;
	//((Sort*)p)->print();
	
}

void Quick::run()
{
	
	pthread_create(&hilo,NULL,ordena,this);
}




void Quick::quickSort(int primero,int ultimo)
{
	int i=primero,j=ultimo;
	int mid = pVector[(primero+ultimo)/2];
	int tmp;

	do
	{
		while(pVector[i]<mid)
			i++;

		while(pVector[j]>mid)
			j--;

		if(i<=j)
		{
			tmp = pVector[j];
			pVector[j]=pVector[i];
			pVector[i]=tmp;

			i++;
			j--;


		}



	}while(i<=j);


	if(primero<j) quickSort(primero,j);
	if(ultimo>i) quickSort(i,ultimo);


}
