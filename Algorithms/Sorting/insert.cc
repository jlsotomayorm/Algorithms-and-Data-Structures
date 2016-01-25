#include "insert.h"

Insert::Insert(int n): Sort(n)
{


}

Insert::~Insert()
{
	delete[] pVector;
}

void Insert::execute()
{
	clock_t begin = clock();
	int index,c;

	for(int i=1;i<size;i++)
	{
		
		index = pVector[i];
		c = i-1;

		while(c>=0 && pVector[c]>index)
		{
			pVector[c+1]= pVector[c];
			c--;

		}

		pVector[c+1]=index;

	}

		
	clock_t end = clock();
	
	tiempo = (double) (end-begin) /CLOCKS_PER_SEC;


}

void* Insert::ordena(void *p)
{
	((Sort*)p)->execute();
	/*cout<<"Ordenado con Insert Sort"<<endl;
	((Sort*)p)->print();*/

}
void Insert::run()
{
	pthread_create(&hilo,NULL,ordena,this);
}
