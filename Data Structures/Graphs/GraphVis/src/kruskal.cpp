#include "kruskal.h"
#include <fstream>
using namespace std;
Kruskal::Kruskal()
{
    raices =0;
}
Kruskal::~Kruskal()
{
    if(raices)
        delete [] raices;
}

void Kruskal::visit(Graph *g,Graph *r)
{
    cout<<"--Iniciando  Kruskal--"<<endl;

    int nVertices = g->getNVertex();
    nVertices++;
    raices = new int[nVertices];
    //Llenamos el vector de ayuda
    for(int i=0;i<nVertices;i++)
    {
        raices[i]=i;
    }

    map<ImageVertex,list<ImageEdge> > graph = g->getDataStructure();
    map<ImageVertex,list<ImageEdge> >::iterator it = graph.begin();

    ofstream os("grafo.dot");
    os<<"Graph G \n {"<<endl;
    os<<"splines = true;"<<endl;

    for(;it!=graph.end();it++)
    {
        list<ImageEdge>::iterator ini = it->second.begin();
        list<ImageEdge>::iterator fin = it->second.end();

        os<<"\""<<(it->first).getPath()<<"\""<<"[image=\""<<(it->first).getPath()<<"\" label =\"\"];"<<endl;
        for(;ini!=fin;ini++)
        {
            //SI encuentra ambos vertices no agrega la arista repetida
            pair <ImageVertex,ImageVertex> par(it->first,ini->getTarget());
            if(noPairs.find(par)==noPairs.end()  )
            {
                //Almacenamos direcciones de memoria
                aristas.push_back(make_pair(ini->getDist(),make_pair((it->first),ini->getTarget())));
                noPairs[par]=1;
                par.first=par.second;
                par.second=it->first;
                noPairs[par]=1;

            }
        }
    }


    cout<<"Tamaño del array de aristas: "<<aristas.size()<<endl;
    aristas.sort();
    //Escribimos el fichero para graficar dot



    //Comenzamos a armar el MST
    list<pair<int,pair<ImageVertex,ImageVertex> > >::iterator ite = aristas.begin();
    for(;ite!=aristas.end();ite++)
    {


        list<map<ImageVertex,bool> >::iterator b_it = bosque.begin();
        list<map<ImageVertex,bool> >::iterator f1 =bosque.end();
        list<map<ImageVertex,bool> >::iterator f2 =bosque.end();

        //Flags para determinar la posicion
        int found1=-1;
        int found2 =-1;

        for(int i=0;b_it!=bosque.end();b_it++,i++)
        {

            if(b_it->find((ite->second).first)!= b_it->end())
            {
                f1=b_it;
                found1=i;
            }
            if(b_it->find((ite->second).second)!= b_it->end())
            {
                found2=i;
                f2=b_it;
            }

        }



      //  cout<<"Intentando con: "<<(ite->second).first.getPath()<<"->"<<ite->first<<"->"<<(ite->second).second.getPath()<<endl;
       // cout<<"Con found1: "<<found1<<" y found2: "<<found2<<endl;

        //Utilizamos el arreglo Uniones para indicar que dos arboles han sido unidos
        //Si encontramos dos nodos que pertenecen a un mismo arbol no lo añadimos pues formario ciclos.
        //Chekeamos los posibles casos

        //Uno: No se encuentra ninguno de los dos

        if(found1==-1&& found2==-1)
        {
            map<ImageVertex,bool> tree;
            tree[(ite->second).first]=true;
            tree[(ite->second).second]=true;

            bosque.push_back(tree);



              cout<<"Adding: "<<(ite->second).first.getPath()<<"->"<<ite->first<<"->"<<(ite->second).second.getPath()<<endl;
              cout<<"Caso 1 ! CUIDADO"<<endl;
            r->addVertex((ite->second).first);
            r->addVertex((ite->second).second);
            r->addEdge((ite->second).first,(ite->second).second,ite->first);
            os<<"\""<<(ite->second).first.getPath()<<"\""<<" -- "<<"\""<<(ite->second).second.getPath()<<"\""<<"[len = "<<ite->first/5<<"];"<<endl;
        }
        else
        {
            //Dos: Uno de los vertices esta en un arbol
            if(found1==-1)
            {
                f2->insert(make_pair((ite->second).first,true));
                //Insertamos al grafo
                  cout<<"Adding: "<<(ite->second).first.getPath()<<"->"<<ite->first<<"->"<<(ite->second).second.getPath()<<endl;
                  cout<<"Caso 2 ! CUIDADO"<<endl;
                 r->addVertex((ite->second).first);
                 r->addEdge((ite->second).first,(ite->second).second,ite->first);
                 os<<"\""<<(ite->second).first.getPath()<<"\""<<" -- "<<"\""<<(ite->second).second.getPath()<<"\""<<"[len = "<<ite->first/5<<"];"<<endl;
            }
            else
            {
                if(found2==-1)
                {
                    f1->insert(make_pair((ite->second).second,true));
                    //Insertamos al grafo
                      cout<<"Adding: "<<(ite->second).first.getPath()<<"->"<<ite->first<<"->"<<(ite->second).second.getPath()<<endl;
                      cout<<"Caso 2! CUIDADO"<<endl;
                    r->addVertex((ite->second).second);
                    r->addEdge((ite->second).first,(ite->second).second,ite->first);
                    os<<"\""<<(ite->second).first.getPath()<<"\""<<" -- "<<"\""<<(ite->second).second.getPath()<<"\""<<"[len = "<<ite->first/5<<"];"<<endl;
                }
                else
                {
                    //Tres: Los dos vertices fueron encontrados pero estan en diferentes arboles
                     //Unimos los arboles


                    int pu,pv;
                    pu = findSet(found1);
                    pv = findSet(found2);
                    if(pu!=pv)
                    {

                        raices[pu]=raices[pv];
                      //Insertamos al grafo
                        cout<<"Adding: "<<(ite->second).first.getPath()<<"->"<<ite->first<<"->"<<(ite->second).second.getPath()<<endl;
                        cout<<"Caso 3 ! CUIDADO"<<endl;
                        r->addEdge((ite->second).first,(ite->second).second,ite->first);
                        os<<"\""<<(ite->second).first.getPath()<<"\""<<" -- "<<"\""<<(ite->second).second.getPath()<<"\""<<"[len = "<<ite->first/5<<"];"<<endl;
                    }
                }


            }


        }
    }

    cout<<"--Finalizando Kruskal--"<<endl;
    os<<"}";
    os.close();
}

int Kruskal::findSet(int a)
{
    if(a != raices[a])
    {
        raices[a] = findSet(raices[a]);

    }

    return raices[a];
}
