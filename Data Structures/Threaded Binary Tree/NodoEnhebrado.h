 #ifndef NODO_ARBOLBB
#define NODO_ARBOLBB
#include <iostream>
using namespace std;
class Nodo_ArbolBB{
	private:
	int dato;
   Nodo_ArbolBB* izquierdo;
   Nodo_ArbolBB *derecho;
   bool hiloI;
   bool hiloD;

   public:
  	Nodo_ArbolBB(int dat,Nodo_ArbolBB *izq,Nodo_ArbolBB *der){
   	dato=dat;
      izquierdo=izq;
      derecho = der;
       hiloI=hiloD=false;
   }

   Nodo_ArbolBB(int dat){
            dato=dat;
            izquierdo=NULL;
            derecho=NULL;
            hiloI=hiloD=false;
   }

   Nodo_ArbolBB(){
         	izquierdo=NULL;
            derecho=NULL;
            hiloI=hiloD=false;

   }
   Nodo_ArbolBB* Sucesor();
  friend class ArbolBB;

};

Nodo_ArbolBB* Nodo_ArbolBB::Sucesor(){
	Nodo_ArbolBB* aux=derecho;
		if(derecho!=NULL){
              if(hiloD)
              		return (derecho);
              else{

                  while(!aux->hiloI){
                  	aux=aux->izquierdo;
                  }
                 return aux;

              }
      }

      else{

         return NULL;
      }


}
#endif
