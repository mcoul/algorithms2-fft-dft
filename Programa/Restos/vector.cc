

#include <iostream>
#include <cmath>

using namespace std


// Constructor por defecto
//
template <class T>
vector<T>::vector()
{
	vector_=NULL;
	length_=0;
}

// Constructor "vacio" con longitud predeterminada
//
template <class T>
vector<T>::vector(const size_t l)
{
	length_=l;
	vector_= new T[length_];
}

// Operador indexación
//
template <class T>
T& vector<T>::operator[](const size_t i)
{
	if(i>length_)
	{	cerr<<"Error: Could not index vector"<<endl;
		exit(1);
	}

	else
		return vector_[i];
}

// Operador asignación



// Constructor por copia
//
template <class T>
vector<T>::vector(const T& V)
{
	length_= V.length;
	vector_= new T[length_];



}	























