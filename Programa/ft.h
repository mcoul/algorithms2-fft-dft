#ifndef _FT_H_INCLUDED_
#define _FT_H_INCLUDED_


// Aquí se debe definir la clase ft, la cual será abstracta. Ésta se encarga
// de indicar el método de cálculo a utilizar (i.e. DFT, FFT).
//
// Asímismo, se deben definir las clases "hijas" como DFT y FFT.

#include <string>
#include <vector>
#include <iostream>
#include "complejo.h"

using namespace std;

//// FLAGS ////

#define AMOUNT_OF_F_METHODS 6
typedef enum {	FT_FLAG_DFT=0, 
		FT_FLAG_IDFT=1,
		FT_FLAG_FFT=2,
		FT_FLAG_IFFT=3,
		FT_FLAG_FFT_ITER=4,
		FT_FLAG_IFFT_ITER=5} ft_flag_t;

#define AMOUNT_OF_R_METHODS 2
typedef enum {	IFT_FLAG_IDFT=0,
		IFT_FLAG_IFFT=1} ift_flag_t;

//// DICCIONARIOS /////
const static string FT_FLAGS[AMOUNT_OF_F_METHODS]={"dft","idft","fft","ifft","fft-iter","ifft-iter"};
const static string IFT_FLAGS[AMOUNT_OF_R_METHODS]={"idft","ifft"};


class ft 
{
	public:
		virtual void calc(vector<complejo>&)=0;
		// Las siguientes funciones son llamadas
		// por la función proc() que al finalizar
		// llama al destructor.
		ft* get_f_method(const ft_flag_t);
		ft* get_r_method(const ift_flag_t);
};



class dft : public ft
{
	public:
		virtual void calc(vector<complejo>&);
		dft(){}
		~dft(){}
};



class idft : public ft
{
	public:
		virtual void calc(vector<complejo>&);

		idft(){}
		~idft(){}
};



class fft : public ft
{
	public:
		virtual void calc(vector<complejo>&);

		fft(){}
		~fft(){}	

};


class ifft : public ft
{
	public:
		virtual void calc(vector<complejo>&);

		ifft(){}
		~ifft(){ }

};

class fft_iter : public ft
{
	public:
		virtual void calc(vector<complejo>&)
		{
		       	cout<<"fft-iter"<<endl;
		}
		fft_iter(){}
		~fft_iter(){} 
};


class ifft_iter : public ft
{
	public:
		virtual void calc(vector<complejo>&)
		{
		       	cout<<"ifft-iter"<<endl;
		}
		ifft_iter(){}
		~ifft_iter(){}

};


#endif
