#include <iostream>

using namespace std;
#define MAX 10

class prims
{
	private : int cost[MAX][MAX], tree[MAX][MAX];
		  int n;
	public  : void readmatrix();
		  int spanningtree(int);
		  void display(int);
};

void prims :: readmatrix()
{
	int i, j;
	cout << "\nIngrese el numero de nodos en el Grafo : ";
	cin  >> n;
	cout << "\nIngrese los pesos de las aristas del Grafo\n\n";
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			cin >> cost[i][j];
}

int prims :: spanningtree(int src)
{

	int visited[MAX], d[MAX], parent[MAX];
	int i, j, k, min, u, v, stcost;
	for (i = 1; i <= n; i++)
	{

	
		d[i] = cost[src][i];
		visited[i] = 0;
		parent[i] = src;
	}


	visited[src] = 1;
	stcost = 0;
	k = 1;
	for (i = 1; i < n; i++)
	{
		min = 999;
		for (j = 1; j <= n; j++)
		{
			if (!visited[j] && d[j] < min)
			{
				min = d[j];
				u = j;
			}
		}
		visited[u] = 1;
		stcost = stcost + d[u];
		tree[k][1] = parent[u];
		tree[k++][2] = u;
		for (v = 1; v <= n; v++)
			if (!visited[v] && (cost[u][v] < d[v]))
			{
				d[v] = cost[u][v];
				parent[v] = u;
			}
	}
	return (stcost);
}

void prims :: display(int cost)
{
	int i;
	cout << endl<<"Los nodos que forman el arbol son\n\n";
	for (i = 1; i < n; i++)
		cout << tree[i][1] << " " << tree[i][2] << endl;
	cout << endl<<"El peso del arbol de expansion minima es : " << cost<<endl;
}

int main()
{
	int source, treecost;
	prims pri;
	pri.readmatrix();
	cout << endl<<"Ingres el nodo origen ";
	cin  >> source;
	treecost = pri.spanningtree(source);
	pri.display(treecost);
	return 0;
}

