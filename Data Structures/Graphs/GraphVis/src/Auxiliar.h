#ifndef AUXILIAR_H
#define AUXILIAR_H
#include <iostream>
//#include <graphviz/gvc.h>
using namespace std;
static inline Agraph_t* _agopen(string name, int kind)
{


    return agopen(const_cast<char *>(name.c_str()), kind);
}

// Add an alternative value parameter to the method for getting an object's attribute
static inline QString _agget(void *object, QString attr, QString alt=QString())
{
    QString str=agget(object, const_cast<char *>(qPrintable(attr)));

    if(str==QString())
        return alt;
    else
        return str;
}

// Directly use agsafeset which always works, contrarily to agset
static inline int _agset(void *object, string attr, string value)
{
    return agsafeset(object, const_cast<char *>((attr).c_str()),
                     const_cast<char *>((value).c_str()),
                     const_cast<char *>((value).c_str()));
}


static inline Agsym_t* _agnodeattr(Agraph_t * graph,string name,string value)
{
    return agnodeattr(graph,const_cast<char*>(name.c_str()),const_cast<char*>((value).c_str()));
}

static inline Agnode_t* _agnode(Agraph_t* graph,string name)
{
    return agnode(graph,const_cast<char*>(name.c_str()));
}

static inline Agsym_t* _agedgeattr(Agraph_t * graph,string name,string value)
{
    return agedgeattr(graph,const_cast<char*>((name).c_str()),const_cast<char*>((value).c_str()));
}



#endif // AUXILIAR_H
