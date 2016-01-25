#ifndef NODO
#define NODO
#include <iostream>
using namespace std;
template<class T>
class Lista;

template<class T>
class Nodo
{
   friend class Lista<T>;
   typedef Nodo<T> * pNodo;
   private:
       T       m_Dato;
       pNodo   m_Sig;
       pNodo   m_Ant;
   public:
      Nodo(T d):m_Dato(d),m_Sig(0),m_Ant(0){}
      void matate()
      {
         if(m_Sig) m_Sig->matate();
         delete this;
      }
      void print(ostream &os)
      {
         if(m_Sig) m_Sig->print(os);
         cout<<m_Dato<<" ";
      }
      pNodo getSig()
      {
         return m_Sig;
      }
       pNodo getAnt()
      {
         return m_Ant;
      }
      T getDato()
      {
         return m_Dato;
      }
};
#endif

