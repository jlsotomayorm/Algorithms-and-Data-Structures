#include "grafo.h"
int INF = numeric_limits<int>::max();
Grafo::Grafo()
{
}

void Grafo::insertEdge(int nodoS, int nodoD, int peso)
{
    if(graph.find(nodoS)==graph.end())
    {
        cout<<"Insertando :"<<nodoS<<" -> "<<nodoD<<" con peso "<<peso<<endl;
        graph[nodoS].push_back(make_pair(nodoD,peso));
        graph[nodoD].push_back(make_pair(nodoS,peso));
    }
    else
    {
        pair<int,int> buscar(nodoD,peso);
        if(find(graph[nodoS].begin(),graph[nodoS].end(),buscar)==graph[nodoS].end())
        {
            cout<<"Insertando :"<<nodoS<<" -> "<<nodoD<<" con peso "<<peso<<endl;
            graph[nodoS].push_back(make_pair(nodoD,peso));
            graph[nodoD].push_back(make_pair(nodoS,peso));
        }
        else
        {
            cout<<"ya existe"<<endl;
        }
    }
}

void Grafo::dijkstra(int source,map<int,int> &d,map<int,int> &d2,int total)
{
        //Distancias

        map<int,vector<pair<int,int> > >::const_iterator it;
        for(int i=1;i<=total;i++)
        {

                d[i]=INF;
                d2[i]=INF;
        }

        d[source]=0;
        d2[source]=0;
        //Usamos un set como priority queue
        set<pair<int,int> > queue;


        for(it = graph.begin();it!=graph.end();it++)
        {
                int vertice = it->first;
                queue.insert(make_pair(d[vertice],vertice));
        }

        while(!queue.empty())
        {
                int nodoU= queue.begin()->second;
                //Como un pop en la priority
                queue.erase(queue.begin());
                //Todos los demas vertices son inaccesibles
                if(d[nodoU]==INF)
                        break;
                //Visitamos cada arista del nodoU
                vector<pair<int,int> >::const_iterator a_it;
                vector<pair<int,int> > aristas = graph[nodoU];
                for(a_it=aristas.begin();a_it!=aristas.end();a_it++)
                {
                        int v = a_it->first;
                        int peso = a_it->second;

                        int distanciaPorU = d[nodoU]+peso;
                        //Dist anterior
                        int distanciaPorU2 =d2[nodoU]+peso;

                        if(distanciaPorU<d[v])
                        {
                                //Guardamos el valor anterior
                                  d2[v]=d[v];
                                //Actualizamos el valor
                                queue.erase(make_pair(d[v],v));

                                d[v]= distanciaPorU;

                                //Lo volvemos a insertar para que se ordene con su valor actualizado
                                queue.insert(make_pair(d[v],v));
                        }
                        else
                        {
                            if(distanciaPorU2<d2[v])
                            {
                                d2[v]=distanciaPorU2;
                            }
                        }
                }

        }



}

