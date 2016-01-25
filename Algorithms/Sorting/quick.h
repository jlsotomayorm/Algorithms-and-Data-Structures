#include "sort.h"


class Quick : public Sort
{
	public:
		Quick(int n);
		~Quick();
		
		void execute();

		static void* ordena(void *p);
		void run();
		

	private:
		
		void quickSort(int primero,int ultimo);

	


};
