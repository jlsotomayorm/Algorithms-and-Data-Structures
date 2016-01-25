#include "bubble.h"

Bubble::Bubble(int n):Sort(n)
{


}

Bubble ::~Bubble()
{
	delete [] pVector;

}

void Bubble ::execute()
{
	clock_t begin = clock();
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size-i;j++)
		{

			if(pVector[j]>pVector[j+1])
			{
				int tmp = pVector[j];
				pVector[j]=pVector[j+1];
				pVector[j+1]=tmp;
			}

		}


	}

	clock_t end = clock();
	
	tiempo = (double) (end-begin) /CLOCKS_PER_SEC;

}

void* Bubble::ordena(void *p)
{
	((Sort*)p)->execute();
	/*cout<<"Ordenado con Bubble Sort"<<endl;
	((Sort*)p)->print();*/

}
void Bubble::run()
{
	pthread_create(&hilo,NULL,ordena,this);
}
