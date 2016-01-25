#include "sort.h"

Sort::Sort(int n)
{
	pVector = new int [n];
	size = n;
	tiempo=-1;

}

void Sort::print()
{
	for(int i=0;i<size;i++)
		cout<<pVector[i]<<" ";
	cout<<endl;
}

void Sort::llenarWorstCase()
{
	for(int i=0;i<size;i++)
		pVector[i]=size-(i+1);

}

void Sort::llenarBestCase()
{
	for(int i=0;i<size;i++)
		pVector[i]=i;

}

void Sort::llenarRandom()
{
	srand(time(NULL));	

	for(int i=0;i<size;i++)
		pVector[i]=rand()%100;

}

pthread_t* Sort::getThread()
{
	return &hilo;
}

void Sort::setTime(double t)
{
	tiempo = t;
}

double Sort::getTime()
{
	return tiempo;
}
