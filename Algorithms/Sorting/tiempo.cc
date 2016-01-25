#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;
int main()
{

	srand(time(NULL));
	
	int n = rand()%20;
	int m = rand()%10;

	cout<<n<<" "<<m<<endl;

	return 0;
}
