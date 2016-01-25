#ifndef _SORT_
#define _SORT_
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
using namespace std;

class Sort
{
	protected: 
		int * pVector;
		int size;
		pthread_t hilo;
		double tiempo;
	public:
		
		Sort(int n);
		
		void print();
		void llenarWorstCase();
		void llenarBestCase();
		void llenarRandom();
		void setTime(double t);
		double getTime();
		pthread_t * getThread();
		virtual  void execute()=0;
		virtual void run()=0;
		


};

#endif
