#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <iostream>
#include <QPen>
#include <QMouseEvent>
#include <QString>

#include "segmento.h"
#include "funciones.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sc = new QGraphicsScene(ui->view->rect());

    ui->view->setScene(sc);

    QTime time = QTime::currentTime();
    qsrand(time.msec());

    ui->view->installEventFilter(this);

}

MainWindow::~MainWindow()
{
   map<pair<int,int>,Segmento*>::iterator it = mymap.begin();
   for(;it!=mymap.end();it++)
   {
       if(it->second)
        delete it->second;
   }
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

int MainWindow::random(int low , int high)
{


    return qrand() % ((high + 1) - low) + low;
}

int MainWindow::srandom()
{
    return (random(0,1))?random():random()*-1;
}

void MainWindow::on_btn_generar_clicked()
{
    sc->clear();

    cleanMemory();
    mymap.clear();
    //arbol.clear();


    int num = ui->nlineas->text().toInt();

    for(int i=0;i<num;i++)
    {
        int x1 = random();
        int y1 = random();
        int x2 = random();
        int y2 = random();
        sc->addLine(x1,y1,x2,y2);

        Segmento *uno = new Segmento(x1,y1,x2,y2);

        mymap[make_pair(x1,y1)]= uno;

        mymap[make_pair(x2,y2)]= uno;

      //  cola.push(make_pair(x1,y1));
        //cola.push(make_pair(x2,y2));
    }

   vector<pair<int,int> > puntos = findIntersection();

   cout<<puntos.size()<<endl;

   QPen pen(Qt::red);
   pen.setWidth(2);
   for(int i=0;i<puntos.size();i++)
   {

       sc->addEllipse(puntos[i].first-2,puntos[i].second-2,4,4,pen);
   }


}

vector<pair<int,int> > MainWindow::findIntersection()
{
    vector<pair<int,int> > rpta;
    AVL<Segmento> tree;
    while(!mymap.empty())
    {

        map<pair<int,int>,Segmento*>::iterator it = mymap.begin();
        pair<int,int> top = it->first;


        Segmento *p = mymap[top];



        if(p->esIzquierdo(top))
        {
            cout<<"es izquierdo el punto: "<<top.first<<" "<<top.second<<endl;

            //Indicamos que TOP es el punto por el cual se tiene que ordenar
            p->setPuntoEnLinea(top);

            cout<<"El segmento tiene:";
               p->printPoints();

        //    pair< set<Segmento>::iterator, bool> r = arbol.insert(*p);
              Nodo<Segmento>* actual = tree.insertar(*p);
              Nodo<Segmento>* anterior = tree.anterior(actual);
              Nodo<Segmento> * siguiente = tree.siguiente(actual);


            if(anterior)
            {
                //set<Segmento>::iterator it = r.first;
                //it--;

                Segmento t = anterior->getDato();
                cout<<"Comparando :"<<endl;
                t.printActualPoint();
                p->printActualPoint();
                //Si p se intersecta con *it insertamos el punto en la cola;
                pair<int,int> inter;
                if(interseccionSegmentos(*p,t,inter))
                {
                    cout<<"Interseccion en el punto: "<<inter.first<<" "<<inter.second<<endl;


                       //Relacionamos el segmento que interseca para su acceso rapido
                    Segmento * otro =new Segmento(t);
                    p->relacionarSegmento(otro);


                    mymap[inter]=p;
                }


            }

              // set<Segmento>::iterator it = r.first;
              // it++;

               if(siguiente)
               {
                   Segmento t = siguiente->getDato();
                   cout<<"Comparando :"<<endl;
                   t.printActualPoint();
                   p->printActualPoint();
                     //Si p se intersecta con *it insertamos el punto en la cola;
                        pair<int,int> inter;
                   if(interseccionSegmentos(*p,t,inter))
                   {
                        cout<<"Interseccion en el punto: "<<inter.first<<" "<<inter.second<<endl;

                       //Relacionamos el segmento que interseca para su acceso rapido

                       Segmento * otro = new Segmento(t);
                    p->relacionarSegmento(otro);
                       mymap[inter]=p;
                   }
               }


        }
        else
        {
            if(p->esDerecho(top))
            {
                 cout<<"es derecho el punto: "<<top.first<<" "<<top.second<<endl;
                 cout<<"El segmento tiene:";
                    p->printPoints();
                //set<Segmento>::iterator it = arbol.find(*p);

                    Nodo<Segmento> *actual;
                    if(tree.buscar(*p,actual))
                    {

                        Nodo<Segmento>* anterior = tree.anterior(actual);
                        Nodo<Segmento> * siguiente = tree.siguiente(actual);






                            if(anterior)
                            {


                                Segmento*  a = new Segmento(anterior->getDato());



                                if(siguiente)
                                {

                                    Segmento *b = new Segmento(siguiente->getDato());



                                        //Si se intersecan a y b en X
                                     pair<int,int> inter;
                                    if(interseccionSegmentos(*a,*b,inter))
                                    {
                                        cout<<"Interseccion en el punto: "<<inter.first<<" "<<inter.second<<endl;
                                        //y X no esta en la cola la insertamos

                                        if(mymap.find(inter)==mymap.end())
                                        {

                                            //Relacionamos los segmentos
                                            a->relacionarSegmento(b);
                                            mymap[inter]=a;

                                        }

                                    }

                                }

                            }

                }

                    /*
                    //Eliminamos el segmento, pues estamos analizando su extremo derecho
                    if( arbol.erase(*p))
                    {
                        cout<<"Eliminado correctamente"<<endl;
                    }
                    else
                    {
                        cout<<"No se elimino"<<endl;
                    }*/

                    cout<<"Borrando..."<<endl;
                    tree.borrar(*p);
                    cout<<"Eliminado correctamente"<<endl;

            }
            else
            {
                 cout<<"Agregando; "<<top.first<<" "<<top.second<<endl;

                rpta.push_back(top);
                //Sea a y b las segmentos cruzados .

                Segmento *a = mymap[top];
                Segmento *b = a->getSegmentoRelacionado();

                cout<<"Intercambiamos: "<<endl;
                a->printPoints();
                cout<<" con "<<endl;
                b->printPoints();

                Segmento * min,*max;
                if(a->isBelow(*b))
                {
                    min = a;
                    max = b;
                }
                else
                {
                    min = b;
                    max = a;
                }
               /* arbol.erase(*a);
                arbol.erase(*b);
                arbol.insert(*a);
                arbol.insert(*b);*/

                //Intercambiamos su posicion en "arbol" . a encima de b


                //Sea A el de encima de a y B el de abajo de b.
                // Si interseca a con A insertamos en cola
                //Si interseca temp con B insertamos en cola
               // set<Segmento>::iterator it = arbol.find(*a);
                Nodo<Segmento> * nodoa,*nodob;
                tree.buscar(*min,nodoa);
                tree.buscar(*max,nodob);

                tree.swap(nodoa,nodob);

                Nodo<Segmento>* anteriorA = tree.anterior(nodoa);
                Nodo<Segmento>* siguienteB = tree.siguiente(nodob);

                if(anteriorA)
                {


                    Segmento *A = new Segmento(anteriorA->getDato());
                    Segmento *A1 = new Segmento(nodoa->getDato());

                   // it = arbol.find(*b);
                    pair<int,int> inter;
                   if(interseccionSegmentos(*A1,*A,inter))
                   {
                       cout<<"Interseccion en el punto: "<<inter.first<<" "<<inter.second<<endl;
                       cout<<"Por las rectas";
                       A->printPoints();
                       A1->printPoints();
                       if(mymap.find(inter)==mymap.end())
                       {

                           //Relacionamos los segmentos
                           A1->relacionarSegmento(A);
                           mymap[inter]=A1;

                       }
                   }


                }

                if(siguienteB)
                {
                   // it++;
                    Segmento *B= new Segmento(siguienteB->getDato());
                    Segmento *B1= new Segmento(nodob->getDato());

                    pair<int,int> inter;

                   if(interseccionSegmentos(*B1,*B,inter))
                   {
                       if(mymap.find(inter)==mymap.end())
                       {
                            cout<<"Interseccion en el punto: "<<inter.first<<" "<<inter.second<<endl;
                            cout<<"Por las rectas";
                            B->printPoints();
                            B1->printPoints();
                           //Relacionamos los segmentos
                           B1->relacionarSegmento(B);
                           mymap[inter]=B1;

                       }
                   }

                }




            }
        }
            //delete it->second;
           mymap.erase(it);
            tree.preOrder();
    }





    return rpta;
}

 bool MainWindow::eventFilter(QObject *obj, QEvent *event)
 {
     if(event->type()==QEvent::MouseButtonPress)
     {
         QMouseEvent * ev = (QMouseEvent*)event;
         QString a;
         a.setNum(ev->pos().x());
         a.append(" ");
         QString b;
         b.setNum(ev->pos().y());
         a.append(b);

         ui->click->setText(a);

         cout<<ev->pos().x()<<" "<<ev->pos().y()<<endl;
           return true;
     }
     else
     {
         return QObject::eventFilter(obj, event);
     }
 }

 void MainWindow::cleanMemory()
 {

     map<pair<int,int>,Segmento*>::iterator it = mymap.begin();
     for(;it!=mymap.end();it++)
     {
         if(it->second)
          delete it->second;
     }

 }
