#include "sort.h"

class Insert : public Sort
{
	public:

		Insert(int n);
		~Insert();
		void execute();
		static void* ordena(void *p);
		void run();

};
