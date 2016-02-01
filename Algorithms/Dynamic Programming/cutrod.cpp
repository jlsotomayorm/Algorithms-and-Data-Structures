#include <iostream>
#include <vector>
using namespace std;



int memoizedCutRodAux(vector <int> &p,int n,vector<int> &r)
{
	
	
	if(r[n-1]>=0)
	{
		return r[n-1];
	}
	int q;

	if(n==0)
		q=0;

	else
	{
		q=-1;

		for(int i=0;i<n;i++)
			q = max(q,p[i]+memoizedCutRodAux(p,n-i-1,r));
	}

	r[n-1]=q;

	return q;

}

int memoizedCutRod(vector <int> &p,int n)
{
	vector<int> r(n);

	for(int i=0;i<n;i++)
		r[i]=-1;

	for(int i=0;i<n;i++)
		cout<<r[i]<<" ";
	return memoizedCutRodAux(p,n,r);
}
int main()
{
	int n;
	vector <int> p;
	cout<<"Ingrese el tamaño de la varilla"<<endl;
	cin>>n;

	
	cout<<"Ingrese los precios en orden"<<endl;
	for(int i=0;i<10;i++)
	{
		int tmp;
		cin>>tmp;
		p.push_back(tmp);
	}

	cout<<memoizedCutRod(p,n)<<endl;
	return 0;
}
