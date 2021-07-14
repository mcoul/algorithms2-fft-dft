

#include "ft.h"
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

ft* ft::get_f_method(const ft_flag_t flag){
	ft* method;

	switch(flag){
		case FT_FLAG_DFT:	
			method = new dft;
			break;
		case FT_FLAG_IDFT:
			method = new idft;
			break;
		case FT_FLAG_FFT:
			method = new fft;
			break;
		case FT_FLAG_IFFT:
			method = new ifft;
			break;
		case FT_FLAG_FFT_ITER:
			method = new fft_iter;
			break;
		case FT_FLAG_IFFT_ITER:
			method = new ifft_iter;
			break;
	}

	return method;
}

ft* ft::get_r_method(const ift_flag_t flag){
	ft* method;

	switch(flag){
		case IFT_FLAG_IDFT:
			method = new idft;
			break;
		case IFT_FLAG_IFFT:
			method = new ifft;
			break;
	}

	return method;
}

void dft::calc(vector<complejo> &x){

	// Esta es la funcion que realiza la DFT propiamente
	// dicha, mediante el algoritmo "naive" - es decir
	// simplemente calculando la serie de la definicion.
	size_t i=0;

	complejo suma;

	complejo WN0(cos(2*M_PI/(x.size())), -sin(2*M_PI/(x.size())));
	complejo WN(1);


	// Hago la cuenta "in-place", reescribiendo el mismo
	// vector x que me pasan por referencia de manera de 
	// ahorrar memoria.

	for(i=0; i<x.size() ; i++){
		suma += x[i]*WN;
		WN *= WN0;
	}	

	WN = 1;

	for(i=0; i < x.size(); i++){
		x[i] = suma*WN;
		WN *= WN0;
	}

}	
