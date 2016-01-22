#include "campo.h"
class HashMap
{
	private:
		Campo ** tabla;
		int tam;
	public:
		HashMap(int t);
		~HashMap();
		int get(int key);
		void add(int key,int value);


};
