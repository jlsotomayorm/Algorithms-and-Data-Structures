#include <iostream>
#include "hashmap.h"

using namespace std;

int main()
{
	HashMap m(5);
	m.add(0,1);
	m.add(15,4);

	cout<<m.get(15)<<endl;

	return 0;
}
