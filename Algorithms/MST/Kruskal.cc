#include <iostream>
#include <utility>
#include <vector>
#define MAX 10
using namespace std;

class Kruskal
{
	private:
		int cos[MAX][MAX];
		vector< pair<int,int> > tree;
		int nodos;
		int *adyacencia;
		bool formaCiclo(int a,int b);		

	public:

		Kruskal();
		~Kruskal();
		void readMatrix();
		int spanningTree();
		void display(int p);


};

Kruskal::Kruskal()
{
	nodos = 0;
	adyacencia=NULL;
}

Kruskal::~Kruskal()
{
	if(adyacencia!=NULL)
		delete [] adyacencia;
}
void Kruskal::readMatrix()
{
	
	

	cout << "\nIngrese el numero de nodos en el Grafo : ";
	cin  >> nodos;

	adyacencia = new int [nodos];

	cout << "\nIngrese los pesos de las aristas del Grafo\n\n";
	for (int i = 0; i < nodos; i++)
	{
		adyacencia[i]=i;

		for (int j = 0; j < nodos; j++)
			cin >> cos[i][j];

	}

	
	
}
int Kruskal::spanningTree()
{
	int **visited = new int* [nodos];

	int min,peso=0;
	int primero,segundo;

	for(int i=0;i<nodos;i++)
		visited[i]=new int[nodos];

	
	//Iniciamos en 0

	for(int i=0;i<nodos;i++)
	{
		
		for(int j=0;j<nodos;j++)
		{
			
			visited[i][j]=0;
		}
	}
		
	while(tree.size()!=nodos-1)
	{
		min =999;

		for(int i=0;i<nodos;i++)
		{
			for(int j=i+1;j<nodos;j++)
			{
	
				if(cos[i][j]<min&&!visited[i][j])			
				{
					
					min = cos[i][j];	
					primero=i;
					segundo =j;
								
				}

			}


		}

		
		if(!formaCiclo(primero,segundo))
		{
			
			pair <int,int> tmp(primero,segundo);

			tree.push_back(tmp);
			
			for(int i=0;i<nodos;i++)
			{
				if(adyacencia[i]==adyacencia[segundo])
					adyacencia[i]=adyacencia[primero];
			}
			peso+=min;			 
		}

		visited[primero][segundo]=1;

	}


	for(int i=0;i<nodos;i++)
		delete[] visited[i];

	delete [] visited;

	return peso;
}

bool Kruskal::formaCiclo(int a,int b)
{
	
	return (adyacencia[a]!=adyacencia[b])?	false:true;	

}

void Kruskal::display(int peso)
{

	cout<<"Los nodos que forman el arbol son: "<<endl;

	for(int i=0;i<tree.size();i++)
		cout<<tree[i].first<<" "<< tree[i].second<<endl;

	cout<<"El peso del arbol de expansion minima es: "<<peso<<endl;

}

int main()
{
	int peso;

	Kruskal k;
	k.readMatrix();
	peso = k.spanningTree();
	k.display(peso);

}
