#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <queue>
#include <utility>
#include <map>
#include <set>

#include "treeAVL.h"

class Segmento;
using namespace std;
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_btn_generar_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *sc;

    //Lo usamos como una cola de prioridad

    map <pair<int,int>,Segmento*> mymap;
   // set<Segmento> arbol;


    int random(int low = 0, int high=500);
    int srandom();
    vector<pair<int,int> > findIntersection();

    bool eventFilter(QObject *obj, QEvent *event);
    void cleanMemory();
};

#endif // MAINWINDOW_H
