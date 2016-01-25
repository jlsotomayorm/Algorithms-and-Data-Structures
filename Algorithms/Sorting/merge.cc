#include "merge.h"

Merge::Merge(int n):Sort(n)
{


}

Merge::~Merge()
{

	delete [] pVector;
}

void Merge::execute()
{
	clock_t begin = clock();
	mergeSort(0,size-1);
	clock_t end = clock();
	
	tiempo = (double) (end-begin) /CLOCKS_PER_SEC;

}

void* Merge::ordena(void *p)
{
	((Sort*)p)->execute();
	/*cout<<"Ordenado con Merge Sort"<<endl;
	((Sort*)p)->print();*/

}
void Merge::run()
{
	pthread_create(&hilo,NULL,ordena,this);
}

void Merge::combina(int low,int mid,int high)
{

	/* int h,i,j,k;

	int *b = new int [size];
	 h=low;
	 i=low;
	 j=mid+1;

	 while((h<=mid)&&(j<=high))
	 {
		  if(pVector[h]<=pVector[j])
		  {
		   b[i]=pVector[h];
		   h++;
		  }
		  else
		  {
		   b[i]=pVector[j];
		   j++;
		  }
		  i++;
	 }
	 if(h>mid)
	 {
		  for(k=j;k<=high;k++)
		  {
		   b[i]=pVector[k];
		   i++;
		  }
	 }
	 else
	 {
		  for(k=h;k<=mid;k++)
		  {
		   b[i]=pVector[k];
		   i++;
		  }
	 }

	 for(k=low;k<=high;k++) pVector[k]=b[k];*/

	int i,j, cont=0;
	int tamano=high-low+1;
	

	int *tmp=new int[tamano];

	for(i=low;i<=mid;i++,cont++)
	{
		tmp[cont]=pVector[i];
	}

	for(i=high;i>=mid+1;i--,cont++)
	{
		tmp[cont]=pVector[i];
	}

	for(i=0,j=tamano-1,cont=low;i<=j;cont++)	
	{
		if(tmp[i]<=tmp[j])
		{
			pVector[cont]=tmp[i];
			i++;
		}
		else
		{
			pVector[cont]=tmp[j];
			j--;
		}
		
	}
	delete[] tmp;


}

void Merge::mergeSort(int low,int high)
{
	 int mid;
	 if(low<high)
	 {
		  mid=(low+high)/2;
		  mergeSort(low,mid);
		  mergeSort(mid+1,high);
		  combina(low,mid,high);
	}

}
