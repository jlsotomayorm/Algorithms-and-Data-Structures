#include "hashmap.h"
HashMap::HashMap(int t)
{
	tam = t;
	tabla = new Campo*[tam];
	for(int i=0;i<tam;i++)
		tabla[i]=0;
}
HashMap::~HashMap()
{
	for(int i=0;i<tam;i++)
	{
		if(tabla[i])	
			delete tabla[i];
	}

	delete [] tabla;
}
int HashMap::get(int key)
{
	//Se puede utilizar otra funcion hash
	int hash = key%tam;
	while(tabla[hash]!=0 && tabla[hash]->getKey()!=key)
	{
		hash = (hash+1)%tam;
	}

	if(tabla[hash]==0)
		return -1;

	return tabla[hash]->getValue();

}
void HashMap::add(int key,int value)
{
//Se puede utilizar otra funcion hash
	int hash = key%tam;
	while(tabla[hash]!=0 && tabla[hash]->getKey()!=key)
	{
		hash = (hash+1)%tam;
	}

	if(tabla[hash]!=0)
		delete tabla[hash];

	tabla[hash]= new Campo(key,value);
}
