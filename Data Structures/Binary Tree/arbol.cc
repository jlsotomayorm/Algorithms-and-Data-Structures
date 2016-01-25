

#include <iostream>

using namespace std;
class Arbol
{	
	private:

	   class Nodo {
     		public:
      	
     		 Nodo(const int dat,Nodo *izq=NULL, Nodo *der=NULL) :
      		  dato(dat) ,izquierdo(izq), derecho(der) {}
      
      		int dato;
      		Nodo *izquierdo;
      		Nodo *derecho;
   		};

	Nodo *raiz;
  	Nodo *actual;
	void inOrdenR(Nodo *n);
	void preOrdenR(Nodo *n);
	void posOrdenR(Nodo *n);

	public:

		Arbol():raiz(NULL),actual(NULL){}
		~Arbol(){Podar(raiz);}
		void insertar(int d);
		void borrar(int d);
                bool buscar(int d);
		bool Vacio(Nodo* r){return r==NULL;}
		bool EsHoja(Nodo *r){return (r->izquierdo)==NULL&&(r->derecho)==NULL;}
		void Podar(Nodo* &);
		void inOrden();
		void preOrden();
		void posOrden();
		

};

void Arbol::Podar(Nodo*& nodo )

{	

   // Algoritmo recursivo, recorrido en postorden
   if(nodo) {
      Podar(nodo->izquierdo); // Podar izquierdo
      Podar(nodo->derecho);   // Podar derecho
      delete nodo;            // Eliminar nodo
      nodo = NULL;
   }


}
void Arbol::insertar(int dat)
{
	Nodo *padre = NULL;

	actual = raiz;
  
	while(!Vacio(actual) && dat != actual->dato) {
		padre = actual;
     		 if(dat > actual->dato) 
			actual = actual->derecho;
      		else 
			if(dat < actual->dato) 	
			actual = actual->izquierdo;
	}

   
   if(!Vacio(actual)) return;
  
   if(Vacio(padre)) raiz = new Nodo(dat);
  
   else if(dat < padre->dato) padre->izquierdo = new Nodo(dat);
 
   else if(dat > padre->dato) padre->derecho = new Nodo(dat);

}

void Arbol::borrar(int dat)
{
	Nodo *padre = NULL;
   Nodo *nodo;
   int aux;

   actual = raiz;
   
   while(!Vacio(actual)) {
      if(dat == actual->dato) { 

         if(EsHoja(actual)) { 
            if(padre) 

               if(padre->derecho == actual) padre->derecho = NULL;
               else if(padre->izquierdo == actual) padre->izquierdo = NULL;
            delete actual; 
            actual = NULL;
            return;
         }
         else { 
            padre = actual;
            //A la derecha
            if(actual->derecho) {
               nodo = actual->derecho;
               while(nodo->izquierdo) {
                  padre = nodo;
                  nodo = nodo->izquierdo;
               }
            }
            //A la izquierda
            else {
               nodo = actual->izquierdo;
               while(nodo->derecho) {
                  padre = nodo;
                  nodo = nodo->derecho;
               }
            }
         
		//Intecambiamos
            aux = actual->dato;
            actual->dato = nodo->dato;
            nodo->dato = aux;
            actual = nodo;
         }
      }
      else { // Todavía no hemos encontrado el valor, seguir buscándolo
         padre = actual;
         if(dat > actual->dato) actual = actual->derecho;
         else if(dat < actual->dato) actual = actual->izquierdo;
      }
   }


}

bool Arbol::buscar(int dat)
{
	actual = raiz;

   
   while(!Vacio(actual)) {
      if(dat == actual->dato) return true;
      else if(dat > actual->dato) actual = actual->derecho; 
      else if(dat < actual->dato) actual = actual->izquierdo;
   }
   return false;

}

void Arbol::inOrdenR(Nodo * n)
{
	if(n!=NULL)
	{
		inOrdenR(n->izquierdo);
		cout<<n->dato<<" ";
		inOrdenR(n->derecho);
	}

}

void Arbol::preOrdenR(Nodo * n)
{
	if(n!=NULL)
	{
		cout<<n->dato<<" ";
		preOrdenR(n->izquierdo);
		preOrdenR(n->derecho);

	}
}

void Arbol::posOrdenR(Nodo * n)
{
	if(n!=NULL)
	{
		posOrdenR(n->izquierdo);
		posOrdenR(n->derecho);
		cout<<n->dato<<" ";
	}
}

void Arbol::inOrden()
{
	cout<<"Mostrando en InOrden"<<endl;
	inOrdenR(raiz);
	cout<<endl;
}

void Arbol::preOrden()
{
	cout<<"Mostrando en PreOrden"<<endl;
	preOrdenR(raiz);
	cout<<endl;
}

void Arbol::posOrden()
{
	cout<<"Mostrando en PosOrden"<<endl;
	posOrdenR(raiz);
	cout<<endl;
}

int main()
{
	Arbol a;
	a.insertar(10);
	a.insertar(30);
	a.insertar(5);

	a.preOrden();
	a.posOrden();
	a.inOrden();

}

