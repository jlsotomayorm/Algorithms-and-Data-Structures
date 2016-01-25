#include <iostream>
#include <limits.h>
using namespace std;

class Floyd
{
	public:

		Floyd();
		~Floyd();
		void readMatrix();
		void spanningTree();
		void display();

	private:

		int **matriz;
		int ** dist;
		int nodos;
	
};


Floyd::Floyd()
{
	matriz=NULL;
	dist=NULL;
}

Floyd::~Floyd()
{
	if(matriz!=NULL)
	{
		for(int i=0;i<nodos;i++)
		{
			delete [] matriz[i];
			delete [] dist[i];
		}
		delete[] matriz;
		delete[] dist;
	}
	

}

void Floyd::readMatrix()
{

	cout << "\nIngrese el numero de nodos en el Grafo : ";
	cin  >> nodos;

	matriz = new int* [nodos];
	dist = new int* [nodos];

	for(int i=0;i<nodos;i++)
	{
		matriz[i]= new int [nodos];
		dist[i] = new int [nodos];
	}
	cout << "\nIngrese los pesos de las aristas del Grafo\n\n";
	for (int i = 0; i < nodos; i++)
	{
		for (int j = 0; j < nodos; j++)
		{
			cin >> matriz[i][j];
			dist[i][j]= matriz[i][j];
		}
	}

	
}

void Floyd:: spanningTree()
{

	for(int k=0;k<nodos;k++)
		for(int j=0;j<nodos;j++)
			for(int i=0;i<nodos;i++)
				if(dist[i][k]+dist[k][j]<dist[i][j])
					dist[i][j]=dist[i][k]+dist[k][j];
					
}

void Floyd:: display()
{
	if(dist!=NULL)
	{
		cout<<"Matriz de distancias minimas usando el algoritmo de Floyd"<<endl;
		for(int i=0;i<nodos;i++)
		{
			for(int j=0;j<nodos;j++)
				cout<<dist[i][j]<< " ";
		
			cout<<endl;
		}

	}
	else
		cout<<"No has generado ninguna matriz"<<endl;
}


int main()
{
	Floyd d;
	d.readMatrix();
	d.spanningTree();

	d.display();	
	return 0;
}
