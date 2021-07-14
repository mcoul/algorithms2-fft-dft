

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

	complejo suma;

	complejo WN0(cos(2*M_PI/(x.size())), -sin(2*M_PI/(x.size())));
	complejo WN(1);
	complejo WNk(1);

	vector<complejo> aux(x.size());

	// Hago la cuenta "in-place", reescribiendo el mismo
	// vector x que me pasan por referencia de manera de 
	// ahorrar memoria.

	for(size_t k=0; k < aux.size(); k++){
		WNk = WN0.pow(k);
		suma = 0;
		for(size_t n=0; n < x.size(); n++){
			WN = WNk.pow(n);
			suma += x[n]*WN;
			WN *= WN;
		}
	
		aux[k] = suma;
	}

	x = aux;		
}	

void idft::calc(vector<complejo> &x){

	// Esta es la funcion que realiza la DFT propiamente
	// dicha, mediante el algoritmo "naive" - es decir
	// simplemente calculando la serie de la definicion.

	complejo suma;

	complejo WN0(cos(2*M_PI/(x.size())), sin(2*M_PI/(x.size())));
	complejo WN(1);
	complejo WNk(1);

	vector<complejo> aux(x.size());

	// Hago la cuenta "in-place", reescribiendo el mismo
	// vector x que me pasan por referencia de manera de 
	// ahorrar memoria.

	for(size_t k=0; k < aux.size(); k++){
		WNk = WN0.pow(k);
		suma = 0;
		for(size_t n=0; n < x.size(); n++){
			WN = WNk.pow(n);
			suma += x[n]*WN;
			WN *= WN;
		}
	
		aux[k] = suma/aux.size();
	}

	x = aux;		
}


void fft::calc(vector<complejo> &x){

	if(x.size() >= 2){
		vector<complejo> p(x.size()/2);
		vector<complejo> q(x.size()/2);

		for(size_t k=0; k < x.size(); k++){
			
			if( k % 2 == 0)
				p[k/2] = x[k];  // Copio los elems pares
			else
				q[(k-1)/2] = x[k];  // Copio los elems impares
		}

		fft::calc(p);
		fft::calc(q);		

		complejo WN( cos(2*M_PI/x.size()), -sin(2*M_PI/x.size()));

		for(size_t k=0; k < x.size(); k++)
			x[k] = p[k % p.size()] + WN.pow(k)*q[k % q.size()];

	}	

}

void ifft::calc(vector<complejo> &x){

	if(x.size() >= 2){
		vector<complejo> p(x.size()/2);
		vector<complejo> q(x.size()/2);

		for(size_t k=0; k < x.size(); k++){
			
			if( k % 2 == 0)
				p[k/2] = x[k];  // Copio los elems pares
			else
				q[(k-1)/2] = x[k];  // Copio los elems impares
		}

		ifft::calc(p);
		ifft::calc(q);		

		complejo WN( cos(2*M_PI/x.size()), sin(2*M_PI/x.size()));

		for(size_t k=0; k < x.size(); k++)
		{
			x[k] = p[k % p.size()] + WN.pow(k)*q[k % q.size()];
			x[k] = x[k]/2;
		}


	}	


}
