#include <iostream>
using namespace std;

template <class T>
class Cola;

template <class T>
class Nodo
{
	friend class Pila<T>;
	private:
		T m_dato;
		Nodo * m_pSig;
	public:
		Nodo(T dato);
		~Nodo();
		T getDato();
		void setDato(T d);
	

};

template <class T>
Nodo<T>::Nodo(T dato)
{
	m_dato = dato;
}
template <class T>
Nodo<T>::~Nodo()
{


}

template <class T>
T Nodo<T>::getDato()
{
	return m_dato;
}

template <class T>
void Nodo<T>::setDato(T d)
{
	m_dato=d;

}

template <class T>
class Pila
{
	private:
		
		Nodo<T> * p_Last;
	public:
		Pila();
		~Pila();
		void push(T dato);
		void pop();
		bool isEmpty();
		void print();

};
template <class T>
Pila<T>::Pila()
{
	
	p_Last = NULL;


}
template <class T>
Pila<T>::~Pila()
{

	while(!isEmpty())
	{
		pop();
	}
	
}

template <class T>
void Pila<T>::push(T dato)
{
	if (p_Last==NULL)
	{
		p_Last = new Nodo<T>(dato);
		p_Last->m_pSig=NULL;
		

	}
	else
	{
		Nodo<T>* tmp = p_Last;
		
		p_Last = new Nodo<T>(dato);
		p_Last->m_pSig = tmp;


	}

}

template <class T>
void Pila<T>::print()
{
	Nodo<T>* tmp = p_Last;

	while(tmp)
	{
		cout<< tmp->m_dato<<" ";
		tmp = tmp->m_pSig;

	}
	
	cout<<endl;
}

template <class T>
void Pila<T>::pop()
{
	if(p_Last==NULL)
	{
		cout<<"No hay datos en la pila"<<endl;
	}
	else
	{
		Nodo <T>* tmp = p_Last;
		p_Last= p_Last->m_pSig;

		delete tmp;

	}

}
template <class T>
bool Pila<T>::isEmpty()
{
	return (p_Last==NULL);

}

int main()
{
	Pila<int> mypila;

	mypila.push(2);
	mypila.push(3);
	mypila.push(4);
	mypila.push(5);
	mypila.push(1);

	mypila.pop();
	mypila.pop();

	mypila.print();
	return 0;
}




