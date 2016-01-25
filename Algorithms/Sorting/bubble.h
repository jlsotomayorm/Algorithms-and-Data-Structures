#ifndef _BUBBLE_
#define _BUBBLE_

#include "sort.h"

class Bubble : public Sort
{
	public: 
		Bubble(int n);
		~Bubble();
		void execute();
		static void* ordena(void *p);
		void run();



};

#endif
