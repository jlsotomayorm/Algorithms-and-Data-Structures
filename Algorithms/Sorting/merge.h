#ifndef _MERGE_
#define _MERGE_
#include "sort.h"
class Merge : public Sort
{
	public:
		Merge(int n);
		~Merge();
		void execute();

		static void* ordena(void *p);
		void run();
		
	private:

		void mergeSort(int low,int high);
		void combina(int low,int mid,int high);


};

#endif
