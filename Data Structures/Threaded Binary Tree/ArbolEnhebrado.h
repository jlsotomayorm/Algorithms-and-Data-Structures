#ifndef ARBOL_BB
#define ARBOL_BB
#include "NodoEnhebrado.h"
  class ArbolBB{
	private:
   	Nodo_ArbolBB *raiz;
      Nodo_ArbolBB *actual;
   public:
      ArbolBB(){
      	raiz = NULL;
         actual = NULL;
      }
     ~ArbolBB(){

      }
      void Insertar(int v);
      void Borrar (int v);
      bool Buscar (int v);
      bool Vacio (Nodo_ArbolBB *r){
      		return r==NULL;
      }
      bool EsHoja(Nodo_ArbolBB *r);
      bool EsSimilar(ArbolBB *r);
      bool Equilibrado();
      int Sucesor(int x);
      void RecorridoInverso();

      void InOrden();
      void PreOrden();
      void PosOrden();
      int Profundidad();
      int CuentaHojas();
      int Area();
   private:
   	bool Equilibrado(Nodo_ArbolBB *a);
      int CuentaHojas(Nodo_ArbolBB *a);
   	void InOrden(Nodo_ArbolBB *a );
   	void PreOrden(Nodo_ArbolBB *a );
   	void PosOrden(Nodo_ArbolBB *a );
      int Profundidad(Nodo_ArbolBB *r);
      bool SimilarNodos(Nodo_ArbolBB *r,Nodo_ArbolBB *s);
      bool Similar(Nodo_ArbolBB *r,Nodo_ArbolBB *s);
       int Sucesor(Nodo_ArbolBB *a, int x);
      int Sucesor(Nodo_ArbolBB *a);
      void Podar(Nodo_ArbolBB *r);
};

void ArbolBB::Insertar(int v){
	Nodo_ArbolBB *padre = NULL;
   Nodo_ArbolBB *aux = raiz;

   	while(aux!=NULL && v!=aux->dato){
            padre=aux;
            if(v<aux->dato){
            		if(aux->hiloI)
                  	break;
           			 else
            			aux = aux->izquierdo;
      		}else
            	if(v>aux->dato){
               		if(aux->hiloD)
                  		break;
                     else
               			aux=aux->derecho;
               }
      }

      if(aux!=NULL&&!(aux->hiloI) && !(aux->hiloD) )
      return;

      Nodo_ArbolBB *Nuevo;
      Nuevo = new Nodo_ArbolBB(v,NULL,NULL);


      if(padre==NULL){

      	raiz = Nuevo;

      }else{


      	if(v<padre->dato){
         	Nuevo->izquierdo=padre->izquierdo;

            if(padre->izquierdo!=NULL)
            		Nuevo->hiloI=true;

            padre->hiloI=false;
         	padre->izquierdo=Nuevo;
            Nuevo->derecho=padre;
            Nuevo->hiloD=true;
         }else{

            if(v>padre->dato){
            		Nuevo->derecho=padre->derecho;
                  if(padre->derecho!=NULL)
            		Nuevo->hiloD=true;

                  padre->hiloD=false;
            		padre->derecho=Nuevo;

                   Nuevo->izquierdo=padre;
           			 Nuevo->hiloI=true;
            }

         }
      }
}

int ArbolBB::Sucesor(Nodo_ArbolBB* a){
	Nodo_ArbolBB* aux=a->derecho;
		if(a->derecho!=NULL){
              if(a->hiloD)
              		return (a->derecho)->dato;
              else{

                  while(!aux->hiloI){
                  	aux=aux->izquierdo;
                  }
                 return aux->dato;

              }
      }

      else{
      	cout<<"El dato ingresado es el mayor en el arbol";
         return 0;
      }


}

int ArbolBB::Sucesor(Nodo_ArbolBB* a,int x){
    if(a==NULL){
    	cout<<"No se encontro el dato";
    	return 0;
    }
    else{
    		if(x<a->dato)
         	return Sucesor (a->izquierdo,x);
         if(x>a->dato)
         	return Sucesor (a->derecho,x);

         return Sucesor(a);
    }

}

int ArbolBB::Sucesor(int x){

	return Sucesor(raiz,x);
}

void ArbolBB::RecorridoInverso(){
  Nodo_ArbolBB *aux = raiz;
  while(aux->izquierdo){
  aux=aux->izquierdo;
  }
  while(aux){
  	cout<<aux->dato<<" ";
   aux=aux->Sucesor();
  }
}
#endif