#-------------------------------------------------
#
# Project created by QtCreator 2011-10-30T19:48:21
#
#-------------------------------------------------

QT       += core gui

TARGET = Analysis
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gvgraph.cpp \
    gvnode.cpp \
    gvedge.cpp \
    graph.cpp \
    imagevertex.cpp \
    imageedge.cpp \
    graphalgorithm.cpp \
    kruskal.cpp \
    myellipse.cpp \
    gaborextraction.cpp \
    prim.cpp

HEADERS  += mainwindow.h \
    gvgraph.h \
    Auxiliar.h \
    gvnode.h \
    gvedge.h \
    graph.h \
    imagevertex.h \
    imageedge.h \
    graphalgorithm.h \
    kruskal.h \
    myellipse.h \
    gaborextraction.h \
    prim.h
LIBS += -lcdt -lgraph -lgvc  -L /home/jl/Descargas/Torch3vision2.1/lib/Linux_DBG_FLOAT -ltorch
INCLUDEPATH += -I /home/jl/Descargas/Torch3vision2.1/core -I /home/jl/Descargas/Torch3vision2.1/vision2.1/core -I /home/jl/Descargas/Torch3vision2.1/vision2.1/addons -I /home/jl/Descargas/Torch3vision2.1/matrix

FORMS    += mainwindow.ui























