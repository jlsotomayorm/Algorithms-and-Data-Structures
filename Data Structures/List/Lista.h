#ifndef LISTA
#define LISTA
#include "Nodo.h"


template<class T>
class Lista
{
     private:
       Nodo<T> *  m_pHead;
       Nodo<T> *  m_pLast;
       int tam;
     public:
       Lista()
       {
          m_pHead =m_pLast=0;
          tam=0;
       }
       ~Lista()
       {
           if(m_pHead)
               m_pHead->matate();
       }
       int getTam()
       {
           return tam;
       }

       bool find(T d, Nodo<T> ** & p)
       {
            p = &m_pHead;
            while(*p)//
            {
               if ((*p)->m_Dato == d) return true;
               if ((*p)->m_Dato > d)  return false;
               p = &((*p)->m_Sig);
            }
            return false;
       }
       bool  Add(T d)
       {

          Nodo<T> ** q;
          if (find(d,q)) return  false;
          Nodo<T> * nuevo = new Nodo<T>(d);
          tam++;
          nuevo->m_Sig = *q;
          if(*q)
          {
               nuevo->m_Ant = (*q)->m_Ant;
               (*q)->m_Ant=nuevo;
          }
          else
          {
             nuevo->m_Ant=m_pLast;
             m_pLast=nuevo;
           }
          *q = nuevo;
          return true;

       }

       Lista<T> & operator<<(T d)
       {
          Add(d);
          return *this;

       }
       Nodo<T> * getHead()
       {
         return m_pHead;
       }
       Nodo<T> * getLast()
       {
         return m_pLast;
       }

   friend ostream & operator<<(ostream & os, Lista<T> & l)
   {
         l.m_pHead->print(os);
         os<<endl;
         return os;

   }

};
#endif




















