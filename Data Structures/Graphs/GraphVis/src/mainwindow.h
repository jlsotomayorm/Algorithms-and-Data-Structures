#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include "graph.h"
#include <QGraphicsScene>
#include <QList>
#include <Qt>
#include "gaborextraction.h"
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
    void on_drawButton_clicked();

    void on_processButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    GaborExtraction extract;

    void renderGraph(GVGraph& g);


};

#endif // MAINWINDOW_H
