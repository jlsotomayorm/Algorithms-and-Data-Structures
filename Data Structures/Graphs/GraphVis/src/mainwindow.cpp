#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QBrush>
#include <QPen>
#include "kruskal.h"
#include "prim.h"


#include <fstream>
#include <QMessageBox>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    //Construimos la escena
    scene = new QGraphicsScene();
    //Seteamos propiedades del QtGraphicsView
    ui->view->setRenderHint(QPainter::Antialiasing);
    ui->view->setScene(scene);

   /* Graph gr;
    ImageVertex a("bus1.pgm");
    ImageVertex b("b");
    ImageVertex c("c");
    ImageVertex d("d");
    ImageVertex e("e");
    ImageVertex f("f");
    ImageVertex g("g");
    gr.addVertex(a);
    gr.addVertex(b);
    gr.addVertex(c);
    gr.addVertex(d);
    gr.addVertex(e);
    gr.addVertex(f);
    gr.addVertex(g);
    gr.addEdge(a,b,7);
    gr.addEdge(a,d,5);
    gr.addEdge(d,b,9);
    gr.addEdge(b,c,8);
    gr.addEdge(b,e,7);
    gr.addEdge(c,e,5);
    gr.addEdge(d,e,15);
    gr.addEdge(d,f,6);
    gr.addEdge(f,e,8);
    gr.addEdge(e,g,9);
    gr.addEdge(f,g,11);



   //gr.qtRender(scene);

    gr.accept(new Kruskal());
    gr.qtRenderMST(scene);*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_drawButton_clicked()
{
    cout<<"Button Clicked"<<endl;

    if(QMessageBox::question(this,"Confirmacion","Desea buscar imagenes en un directorio y generar su vector caracteristico?",QMessageBox::Cancel|QMessageBox::Ok)==QMessageBox::Ok)
    {
        //Generamos una lista con las imagenes a colores "salida.txt"
      //  system("find /home/jl/Documentos/Programacion/Datos1/Graphs/Graphs-build-desktop-Desktop_Release/ -name '*.jpg' > salida.txt");
         system("find /home/jl/Descargas/image.orig/ -name '*.jpg' > salida.txt");
        cout<<"Finish finding"<<endl;
        system("mogrify -path /home/jl/Documentos/Programacion/Datos1/Analysis/Analysis-build-desktop-Release/Temporal -format pgm @salida.txt");


        ifstream lee("salida.txt");

        ofstream escribe("vectores2.txt");

        string rutaC,rutaG;
        int scale=4;
        int orientation=6;
        int tam = scale*orientation*2;

        lee>>rutaC;

        while(!lee.eof())
        {
            int pos = rutaC.find_last_of("/");
             rutaG =rutaC.substr(pos+1);
             pos = rutaG.find(".");
             rutaG = rutaG.substr(0,pos);
             rutaG+=".pgm";
            string dir = "Temporal/";
            dir+=rutaG;
            double *vector =extract.getFeatureVector(dir,scale,orientation);

            escribe<<rutaC<<endl;
            for(int i=0;i<tam;i++)
            {
                escribe<<vector[i];
                if(i!=tam-1)
                    escribe<<" ";
                else
                    escribe<<endl;
            }

            delete vector;
            lee>>rutaC;

        }


        cout<<"Proceso terminado"<<endl;

        escribe.close();
        lee.close();
    }
    else
    {
        cout<<"Nada"<<endl;
    }


}

void MainWindow::renderGraph(GVGraph &graph)
{
        graph.applyLayout();

        QList<GVNode> nodos = graph.nodes();
        QList<GVEdge> aristas = graph.edges();


      scene = new QGraphicsScene(graph.boundingRect());



      for(QList<GVNode>::iterator it = nodos.begin();it!=nodos.end();it++)
      {
          cout<<"Adding element"<<endl;
          GVNode tmp =*it;
          QGraphicsEllipseItem *elipse =new QGraphicsEllipseItem(tmp.getX(),tmp.getY(),tmp.getWidth(),tmp.getHeight());
          elipse->setBrush(QBrush(Qt::lightGray));

          QPen pen;

          pen.setCapStyle(Qt::RoundCap);
          pen.setStyle(Qt::SolidLine);
          pen.setBrush(Qt::blue);
          pen.setWidth(2);


          elipse->setPen(pen);

          scene->addItem(elipse);
      }

      for(QList<GVEdge>::iterator it=aristas.begin();it!=aristas.end();it++)
      {
          cout<<"Adding edge"<<endl;
          GVEdge tmp = *it;

          QGraphicsPathItem * ruta = new QGraphicsPathItem(tmp.getPath());
            QPen pen;
            pen.setCapStyle(Qt::RoundCap);
            pen.setColor(Qt::blue);
           ruta->setPen(pen);
          scene->addItem(ruta);

      }


      ui->view->setScene(scene);
      ui->view->setRenderHint(QPainter::Antialiasing);

}

void MainWindow::on_processButton_clicked()
{
    ifstream lee("vectores2.txt");
    vector<double *> vectores;
    vector<string> rutas;

    int scale=4;
    int orientation=6;
    int tam = scale*orientation*2;
    string tmp;



    lee>>tmp;

    while(!lee.eof())
    {
        rutas.push_back(tmp);

        double * features = new double[tam];
        double valor;
        for(int i=0;i<tam;i++)
        {
            lee>>valor;
            features[i]=valor;

        }

         vectores.push_back(features);

        lee>>tmp;
    }

    lee.close();

    //TODO calcular distancias y generar grafo.
    Graph gr;

    int rutasTam = rutas.size();
    //Añadimos los vertices del grafo
    for(int i=0;i<rutasTam;i++)
    {
        gr.addVertex(ImageVertex(rutas[i]));

    }

    //Calculamos las distancias y generamos las aristas

    int vecTam = vectores.size();
    for(int i=0;i<vecTam-1;i++)
    {
        for(int j=i+1;j<vecTam;j++)
        {
            double dist =extract.euclideanDistance(vectores[i],vectores[j],tam);
            cout<<"Imagen: "<<rutas[i]<<" distancia: "<<dist<<" con Imagen: "<<rutas[j]<<endl;
            gr.addEdge(ImageVertex(rutas[i]),ImageVertex(rutas[j]),dist);
        }
    }

    //Dibujamos el grafo
     //gr.qtRender(scene);

     //Dibujamos el arbol de expansion minima
     gr.accept(new Kruskal());
     gr.qtRenderMST(scene);


    //Libreamos memoria utilizada

    cout<<"Vectores tam: "<<vectores.size()<<endl;
    cout<<"Rutas tam: "<<rutas.size()<<endl;
    for(int i=0;i<vectores.size();i++)
        delete [] vectores[i];
}
