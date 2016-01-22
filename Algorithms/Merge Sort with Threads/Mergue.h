#ifndef MERGUE_H
#define MERGUE_H
#include "Ordenamiento.h"
#include <boost/thread.hpp>  

class Mergue: public Ordenamiento
{
    private:
		int n_hilos;
		int max_hilos;
    public:
        Mergue();
        void merge_sort(int low,int high);
        void merge(int low,int mid,int high);
        void ordena ();
	void setNHilos(int n);
        virtual ~Mergue();
    protected:

};

#endif // MERGUE_H
