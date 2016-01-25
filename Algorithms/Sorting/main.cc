#include <iostream>
#include <fstream>
#include "quick.h"
#include "bubble.h"
#include "insert.h"
#include "merge.h"
using namespace std;
#define N 10000
int main()
{
	
	ofstream salida("salida.txt");
	/*
	for(int k=10000;k<=1000000;k*=10)
	{
		Sort *p[]={new Quick(k),new Merge (k), new Insert(k),new Bubble(k)};

		for(int i=0;i<4;i++)
			p[i]->llenarRandom();

		for(int i=0;i<4;i++)
			p[i]->run();
	
		for(int i=0;i<4;i++)
			pthread_join(*p[i]->getThread(),NULL);


		
		cout<<p[0]->getTime()<<" ";
		cout<<p[1]->getTime()<<" ";
		cout<<p[2]->getTime()<<" ";
		cout<<p[3]->getTime()<<endl;

		
		for(int i=0;i<4;i++)
			delete p[i];

		Sort *p = new Quick(k);

		p->llenarRandom();
		p->run();

		pthread_join(*p->getThread(),NULL);


		cout<<"Tiempo :"<<p->getTime()<<endl;

		delete p;
		
		
	}

	salida.close();*/

	for(int i=0;i<=100000;i+=500)
	{
		Sort *p = new Merge(i);
	
		p->llenarRandom();
		

		p->run();

		pthread_join(*p->getThread(),NULL);
		
		salida<<i<<" "<<p->getTime()<<endl;

		delete p;
	}

	salida.close();
	
	return 0;

}
