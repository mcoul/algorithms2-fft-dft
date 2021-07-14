#ifndef _VECTOR_H_INCLUDED_
#define _VECTOR_H_INCLUDED_


#include <iostream>
#include <cmath>


template <class T>
class vector 
{
	private:
		size_t length_;
		T * vector_;
	
	public:
		vector();		// Constructor por defecto
		vector(const size_t);	// Constructor "vacio" con long determinada
		T& operator[](const size_t);	// Operador Asignación	
		



		vector(const T&);	// Constructor por Copia
		~vector();		// Destructor por defecto
}


#endif
