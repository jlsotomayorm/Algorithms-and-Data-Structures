#ifndef TREEAVL_H
#define TREEAVL_H
#include <iostream>

using namespace std;
template<class T>
 class AVL;




//-----------------------------------------------------------CLASS NODO--------------------------------------------------------
// Clase Nodo de Arbol AVL:

template<class T>
class Nodo {
  public:
   // Constructor:
   Nodo(const T dat, Nodo<T> *pad=NULL,
        Nodo<T> *izq=NULL, Nodo<T> *der=NULL) :
     dato(dat), padre(pad), izquierdo(izq), derecho(der), FE(0) {}
   // Miembros:
   T dato;
   Nodo<T> *padre;
   Nodo<T> *izquierdo;
   Nodo<T> *derecho;
   int FE;
   T getDato(){ return dato;}
   friend class AVL<T>;
};
//-----------------------------------------------------------CLASS AVL---------------------------------------------------------
template<class T>
class AVL {

  private:
   enum {IZQUIERDO, DERECHO};
   // Punteros de la lista, para cabeza y nodo actual:
   Nodo<T> *raiz;
   Nodo<T> *actual;
   int contador;
   int altura;


  public:
   //Constructor
    AVL() : raiz(NULL), actual(NULL) {}
   // Destructor 
   ~AVL() { Podar(raiz); }

   // Insertar al arbol
   Nodo<T>* insertar( T dat);
   // Borrar un elemento del arbol
   void borrar( T dat);
   // Función de búsqueda:
   bool buscar( T dat,Nodo<T>*& p);
   // Comprobar si el árbol está vacío:
   bool Vacio(Nodo<T> *r) { return r==NULL; }
   // Comprobar si es un nodo hoja:
   bool EsHoja(Nodo<T> *r) { return !r->derecho && !r->izquierdo; }
   // Contar número de nodos:
   int NumeroNodos();
   int AlturaArbol();
   // Calcular altura de un dato:
   int Altura(const T dat);
   // Devolver referencia al dato del nodo actual:
   T &ValorActual() { return actual->dato; }
   // Moverse al nodo raiz:
   void Raiz() { actual = raiz; }
   //Si el arbol esta vacio
   bool isEmpty();

   void inOrder(Nodo<T>* raiz);
   void inOrder();

   void preOrder(Nodo<T>* raiz);
   void preOrder();



   Nodo<T>* anterior(Nodo<T>*p);
   Nodo<T>* siguiente(Nodo<T>*p);
   Nodo<T>* masIzquierdo(Nodo<T> *nodo);
   Nodo<T>* masDerecho(Nodo<T> *nodo);
   void swap(Nodo<T>* uno,Nodo<T>* dos);

  private:
   // Funciones de equilibrado:
   void Equilibrar(Nodo<T> *nodo, int, bool);
   void RSI(Nodo<T>* nodo);
   void RSD(Nodo<T>* nodo);
   void RDI(Nodo<T>* nodo);
   void RDD(Nodo<T>* nodo);
   // Funciones auxiliares
   void Podar(Nodo<T>* &);
   void auxContador(Nodo<T>*);
   void auxAltura(Nodo<T>*, int);
};
template <class T>
void AVL<T>::swap(Nodo<T>* uno,Nodo<T>* dos)
{

    T tmp = uno->dato;
    uno->dato = dos->dato;
    dos->dato=tmp;
}
template <class T>
Nodo<T>* AVL<T>::masDerecho(Nodo<T> *nodo)
{

    if(nodo)
    {
        while(nodo->derecho)
        {
            nodo = nodo->derecho;

        }

        return nodo;
    }
    else
    {
        return NULL;
    }


}
template <class T>
Nodo<T>* AVL<T>::masIzquierdo(Nodo<T> *nodo)
{

    if(nodo)
    {
        while(nodo->izquierdo)
        {
            nodo = nodo->izquierdo;

        }

        return nodo;
    }
    else
    {
        return NULL;
    }
}
template<class T>
Nodo<T>* AVL<T>::anterior(Nodo<T>*pActual)
{
    if(pActual)
    {
        if(pActual->izquierdo)
          {

                    return masDerecho(pActual->izquierdo);
          }
         else
         {
                Nodo<T> *tmp = pActual->padre;
                while(tmp && (tmp->dato> pActual->dato))
                {
                        tmp = tmp->padre;
                }

                return tmp;

        }
    }
    else
    {
        return NULL;
    }
}

template<class T>
Nodo<T>* AVL<T>::siguiente(Nodo<T>*pActual)
{
    if(pActual)
    {
        if(pActual->derecho)
        {

                return masIzquierdo(pActual->derecho);
        }
        else
        {
                Nodo<T> *tmp = pActual->padre;
                while(tmp && (tmp->dato< pActual->dato))
                {
                        tmp = tmp->padre;
                }

               return tmp;

        }
    }
    else
    {
        return NULL;
    }
}


// Poda: borrar todos los nodos a partir de uno, incluido
template<class T>
void AVL<T>::Podar(Nodo<T>* &nodo)
{
   // Algoritmo recursivo, recorrido en postorden
   if(nodo) {
      Podar(nodo->izquierdo); // Podar izquierdo
      Podar(nodo->derecho);   // Podar derecho
      delete nodo;            // Eliminar nodo
      nodo = NULL;
   }
}

// Insertar un dato en el árbol AVL
template<class T>
Nodo<T>* AVL<T>::insertar( T dat)
{
    //cout<<"Insertando Nodo"<<endl;
   Nodo<T> *padre = NULL;


   actual = raiz;
   // Buscar el dato en el árbol, manteniendo un puntero al nodo padre
   while(!Vacio(actual) && dat != actual->dato) {
      padre = actual;
      if(dat > actual->dato) actual = actual->derecho;
      else if(dat < actual->dato) actual = actual->izquierdo;
   }

   // Si se ha encontrado el elemento, regresar sin insertar
   if(!Vacio(actual)) return NULL;
   // Si padre es NULL, entonces el árbol estaba vacío, el nuevo nodo será
   // el nodo raiz
   if(Vacio(padre))
   {
       raiz = new Nodo<T>(dat);
       return raiz;
   }
   // Si el dato es menor que el que contiene el nodo padre, lo insertamos
   // en la rama izquierda
   else if(dat < padre->dato) {
      padre->izquierdo = new Nodo<T>(dat, padre);
    Nodo<T>* nuevo = padre->izquierdo;
      Equilibrar(padre, IZQUIERDO, true);
      return nuevo;
   }
   // Si el dato es mayor que el que contiene el nodo padre, lo insertamos
   // en la rama derecha
   else if(dat > padre->dato) {
      padre->derecho = new Nodo<T>(dat, padre);
      Nodo<T>* nuevo = padre->derecho;
      Equilibrar(padre, DERECHO, true);
      return nuevo;
   }
}

// Equilibrar árbol AVL partiendo del nodo nuevo
template<class T>
void AVL<T>::Equilibrar(Nodo<T> *nodo, int rama, bool nuevo)
{
   bool salir = false;

   // Recorrer camino inverso actualizando valores de FE:
   while(nodo && !salir) {
      if(nuevo)
         if(rama == IZQUIERDO) nodo->FE--; // Depende de si añadimos ...
         else                  nodo->FE++;
      else
         if(rama == IZQUIERDO) nodo->FE++; // ... o borramos
         else                  nodo->FE--;
      if(nodo->FE == 0) salir = true; // La altura de las rama que
                                      // empieza en nodo no ha variado,
                                      // salir de Equilibrar
      else if(nodo->FE == -2) { // Rotar a derechas y salir:
         if(nodo->izquierdo->FE == 1) RDD(nodo); // Rotación doble
         else RSD(nodo);                         // Rotación simple
         salir = true;
      }
      else if(nodo->FE == 2) {  // Rotar a izquierdas y salir:
         if(nodo->derecho->FE == -1) RDI(nodo); // Rotación doble
         else RSI(nodo);                        // Rotación simple
         salir = true;
      }
      if(nodo->padre)
      {
          if(nodo->padre->derecho == nodo)
              rama = DERECHO;
          else
              rama = IZQUIERDO;
      }
      nodo = nodo->padre; // Calcular FE, siguiente nodo del camino.
   }
}

// Rotación doble a derechas
template<class T>
void AVL<T>::RDD(Nodo<T>* nodo)
{

   Nodo<T> *Padre = nodo->padre;
   Nodo<T> *P = nodo;
   Nodo<T> *Q = P->izquierdo;
   Nodo<T> *R = Q->derecho;
   Nodo<T> *B = R->izquierdo;
   Nodo<T> *C = R->derecho;

   if(Padre)
     if(Padre->derecho == nodo) Padre->derecho = R;
     else Padre->izquierdo = R;
   else raiz = R;

   // Reconstruir árbol:
   Q->derecho = B;
   P->izquierdo = C;
   R->izquierdo = Q;
   R->derecho = P;

   // Reasignar padres:
   R->padre = Padre;
   P->padre = Q->padre = R;
   if(B) B->padre = Q;
   if(C) C->padre = P;

   // Ajustar valores de FE:
   switch(R->FE) {
      case -1: Q->FE = 0; P->FE = 1; break;
      case 0:  Q->FE = 0; P->FE = 0; break;
      case 1:  Q->FE = -1; P->FE = 0; break;
   }
   R->FE = 0;
}

// Rotación doble a izquierdas
template<class T>
void AVL<T>::RDI(Nodo<T>* nodo)
{

   Nodo<T> *Padre = nodo->padre;
   Nodo<T> *P = nodo;
   Nodo<T> *Q = P->derecho;
   Nodo<T> *R = Q->izquierdo;
   Nodo<T> *B = R->izquierdo;
   Nodo<T> *C = R->derecho;

   if(Padre)
     if(Padre->derecho == nodo) Padre->derecho = R;
     else Padre->izquierdo = R;
   else raiz = R;

   // Reconstruir árbol:
   P->derecho = B;
   Q->izquierdo = C;
   R->izquierdo = P;
   R->derecho = Q;

   // Reasignar padres:
   R->padre = Padre;
   P->padre = Q->padre = R;
   if(B) B->padre = P;
   if(C) C->padre = Q;

   // Ajustar valores de FE:
   switch(R->FE) {
      case -1: P->FE = 0; Q->FE = 1; break;
      case 0:  P->FE = 0; Q->FE = 0; break;
      case 1:  P->FE = -1; Q->FE = 0; break;
   }
   R->FE = 0;
}

// Rotación simple a derechas
template<class T>
void AVL<T>::RSD(Nodo<T>* nodo)
{

   Nodo<T> *Padre = nodo->padre;
   Nodo<T> *P = nodo;
   Nodo<T> *Q = P->izquierdo;
   Nodo<T> *B = Q->derecho;

   if(Padre)
     if(Padre->derecho == P) Padre->derecho = Q;
     else Padre->izquierdo = Q;
   else raiz = Q;

   // Reconstruir árbol:
   P->izquierdo = B;
   Q->derecho = P;

   // Reasignar padres:
   P->padre = Q;
   if(B) B->padre = P;
   Q->padre = Padre;

   // Ajustar valores de FE:
   P->FE = 0;
   Q->FE = 0;
}

// Rotación simple a izquierdas
template<class T>
void AVL<T>::RSI(Nodo<T>* nodo)
{

   Nodo<T> *Padre = nodo->padre;
   Nodo<T> *P = nodo;
   Nodo<T> *Q = P->derecho;
   Nodo<T> *B = Q->izquierdo;

   if(Padre)
     if(Padre->derecho == P) Padre->derecho = Q;
     else Padre->izquierdo = Q;
   else raiz = Q;

   // Reconstruir árbol:
   P->derecho = B;
   Q->izquierdo = P;

   // Reasignar padres:
   P->padre = Q;
   if(B) B->padre = P;
   Q->padre = Padre;

   // Ajustar valores de FE:
   P->FE = 0;
   Q->FE = 0;
}

// Eliminar un elemento de un árbol AVL
template<class T>
void AVL<T>::borrar( T dat)
{


   Nodo<T> *padre = NULL;
   Nodo<T> *nodo;
   T aux;

   actual = raiz;
   // Mientras sea posible que el valor esté en el árbol
   while(!Vacio(actual))
   {
      if(dat == actual->dato)
       {
          // Si el valor está en el nodo actual
         if(EsHoja(actual))
          {
             // Y si además es un nodo hoja: lo borramos
            if(padre) // Si tiene padre (no es el nodo raiz)
             {
                // Anulamos el puntero que le hace referencia
                if(padre->derecho == actual)
                {
                    padre->derecho = NULL;
                }
               else
                {
                   if(padre->izquierdo == actual)
                       padre->izquierdo = NULL;
                }
            }
            else
            {
                raiz = NULL;
            }
            delete actual; // Borrar el nodo
            actual = NULL;
            // El nodo padre del actual puede ser ahora un nodo hoja, por lo tanto su
            // FE es cero, pero debemos seguir el camino a partir de su padre, si existe.
            if(padre && ((padre->derecho == actual && padre->FE == 1) || (padre->izquierdo == actual && padre->FE == -1)))
            {
               padre->FE = 0;
               actual = padre;
               padre = actual->padre;
            }
            if(padre)
            {
               if(padre->derecho == actual)
                {
                    Equilibrar(padre, DERECHO, false);
                }
               else
                {
                   Equilibrar(padre, IZQUIERDO, false);
                }
           }
            return;
         }
         else { // Si el valor está en el nodo actual, pero no es hoja
            // Buscar nodo
            padre = actual;
            // Buscar nodo más izquierdo de rama derecha
            if(actual->derecho) {
               nodo = actual->derecho;
               while(nodo->izquierdo) {
                  padre = nodo;
                  nodo = nodo->izquierdo;
               }
            }
            // O buscar nodo más derecho de rama izquierda
            else {
               nodo = actual->izquierdo;
               while(nodo->derecho) {
                  padre = nodo;
                  nodo = nodo->derecho;
               }
            }
            // Intercambiar valores de no a borrar u nodo encontrado
            // y continuar, cerrando el bucle. El nodo encontrado no tiene
            // por qué ser un nodo hoja, cerrando el bucle nos aseguramos
            // de que sólo se eliminan nodos hoja.
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



// Buscar un valor en el árbol
template<class T>
bool AVL<T>::buscar( T dat,Nodo<T>* &p)
{
   actual = raiz;

   // Todavía puede aparecer, ya que quedan nodos por mirar
   while(!Vacio(actual)) {
      if(dat == actual->dato)
       {
            p=actual;
            return true; // dato encontrado
       }
      else if(dat > actual->dato) actual = actual->derecho; // Seguir
      else if(dat < actual->dato) actual = actual->izquierdo;
   }

   return false; // No está en árbol
}

// Calcular la altura del nodo que contiene el dato dat
template<class T>
int AVL<T>::Altura(const T dat)
{
   int altura = 0;
   actual = raiz;

   // Todavía puede aparecer, ya que quedan nodos por mirar
   while(!Vacio(actual)) {
      if(dat == actual->dato) return altura; // dato encontrado
      else {
         altura++; // Incrementamos la altura, seguimos buscando
         if(dat > actual->dato) actual = actual->derecho;
         else if(dat < actual->dato) actual = actual->izquierdo;
      }
   }
   return -1; // No está en árbol
}

// Contar el número de nodos
template<class T>
 int AVL<T>::NumeroNodos()
{
   contador = 0;

   auxContador(raiz); // FUnción auxiliar
   return contador;
}

// Función auxiliar para contar nodos. Función recursiva de recorrido en
//   preorden, el proceso es aumentar el contador
template<class T>
void AVL<T>::auxContador(Nodo<T> *nodo)
{
   contador++;  // Otro nodo
   // Continuar recorrido
   if(nodo->izquierdo) auxContador(nodo->izquierdo);
   if(nodo->derecho)   auxContador(nodo->derecho);
}

// Calcular la altura del árbol, que es la altura del nodo de mayor altura.
template<class T>
 int AVL<T>::AlturaArbol()
{
   altura = 0;

   auxAltura(raiz, 0); // Función auxiliar
   return altura;
}

// Función auxiliar para calcular altura. Función recursiva de recorrido en
// postorden, el proceso es actualizar la altura sólo en nodos hojas de mayor
// altura de la máxima actual
template<class T>
void AVL<T>::auxAltura(Nodo<T> *nodo, int a)
{
   // Recorrido postorden
   if(nodo->izquierdo) auxAltura(nodo->izquierdo, a+1);
   if(nodo->derecho)   auxAltura(nodo->derecho, a+1);
   // Proceso, si es un nodo hoja, y su altura es mayor que la actual del
   // árbol, actualizamos la altura actual del árbol
   if(EsHoja(nodo) && a > altura) altura = a;
}

template<class T>
bool AVL<T>::isEmpty()
{
    return raiz==NULL;
}
template<class T>
void AVL<T>::inOrder(Nodo<T>* raiz)
{

    if(raiz)
    {
        inOrder(raiz->izquierdo);
        cout<<raiz->dato<<" ";
        inOrder(raiz->derecho);

    }
}
template<class T>
void AVL<T>::inOrder()
{
    cout<<"Inorden"<<endl;
    inOrder(raiz);
    cout<<endl;
}

template<class T>
void AVL<T>::preOrder(Nodo<T>* raiz)
{

    if(raiz)
    {
        cout<<raiz->dato<<" ";
        preOrder(raiz->izquierdo);

        preOrder(raiz->derecho);

    }
}
template<class T>
void AVL<T>::preOrder()
{
    cout<<"Preorden"<<endl;
    preOrder(raiz);
    cout<<endl;
}



#endif // TREEAVL_H
