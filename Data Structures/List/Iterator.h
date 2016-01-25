#include "Lista.h"

template <class T>
class Iterator 
{
   public:
      virtual void begin()=0;
      virtual void end()=0;
      virtual void operator ++()=0;
      virtual void operator --()=0;
      virtual T getDato()=0;
      virtual bool terminate()=0;
    virtual void setAct(Nodo<T>* n)=0;


};

template <class T>
class IterLista:public Iterator<T>
{
   private:
      Nodo<T> *pAct;
      Nodo<T> *pHead;
      Nodo<T> *pLast;
   public:
    IterLista(Lista <T> &l);
    void begin();
    void end();
    void operator ++();
    void operator --();
    T getDato();
    void setAct(Nodo<T> * n);
    bool terminate();
   
 
};
template <class T>
 IterLista<T>:: IterLista(Lista <T> &l)
 {
   pHead=l.getHead();
   pAct=pHead;
   pLast=l.getLast();
   
 }
 
 template <class T>
 void IterLista<T>:: begin()
 {
    pAct=pHead;
 }
  
  template <class T>
 void IterLista<T>:: end()
 {
   
      
      pAct=pLast;
         
 } 
  template <class T>
 bool IterLista<T>:: terminate()
 {
    if(!pAct)
      {
        pAct=pHead;
        return true;
      }
    return false;  
        
 }
   template <class T>
 void IterLista<T>::operator ++()
 {
     if(pAct->getSig())
         pAct=pAct->getSig();//hacer
 }
 template <class T>
  void IterLista<T>::operator --()
 {
     if(pAct->getAnt())
         pAct=pAct->getAnt();//hacer
 }

  template <class T>
   void IterLista<T>::setAct(Nodo<T> *n)
  {
      pAct=n;
  }
   template <class T>
 T  IterLista<T>::getDato()
 {
   return pAct->getDato();
 }
 /*
int main()
{
   Lista<int> A;
   A<<23<<78<<66<<5<<9<<78<<9<<64<<99;
  // cout<<A<<endl;
   IterLista<int > I(A);
   cout<<"ascendente :"<<endl;
   for(I.begin() ;!I.terminate();++I)
   {
       cout<<I.getDato()<<endl;
   }
      cout<<"descendente :"<<endl;
    for(I.end() ;!I.terminate();--I)
   {
       cout<<I.getDato()<<endl;
   } 
return 1;
}*/
//tres patrones ... singleton iterator pesso mossso  memento
/*
a  singleton
b  iterator
c  peso mosca   10^9 circulitos de 16 GB a 4 Gb de ram cambia uno cambia todo .... 
d memento    atras siguiente   pila cola 
e  observer  varios grafico una sola dat a
*/
  
