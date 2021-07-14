
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>

#include "cmdline.h"
#include "complejo.h"
#include "ft.h"
#include "proc.h"

using namespace std;

static void opt_input(string const &);		// Setea el flujo de entrada
static void opt_output(string const &);		// Setea el flujo de salida
static void opt_forward_op(string const &);	// Determina el flag de FT
static void opt_reverse_op(string const &);	// Determina el flag de IFT
static void opt_block_shift(string const &);	// Setea el valor de s_length
static void opt_taps(string const &);		// Completa el vector taps
static void opt_help(string const &);		// Imprime las ayudas

// Tabla de opciones de línea de comando. El formato de la tabla
// consta de un elemento por cada opción a definir. A su vez, en
// cada entrada de la tabla tendremos:
//
// o La primera columna indica si la opción lleva (1) o no (0) un
//   argumento adicional.
// 
// o La segunda columna representa el nombre corto de la opción.
// 
// o Similarmente, la tercera columna determina el nombre largo.
// 
// o La cuarta columna contiene el valor por defecto a asignarle
//   a esta opción en caso que no esté explícitamente presente
//   en la línea de comandos del programa. Si la opción no tiene
//   argumento (primera columna nula), todo esto no tiene efecto.
//
// o La quinta columna apunta al método de parseo de la opción,
//   cuyo prototipo debe ser siempre void (*m)(string const &arg);
//
// o La última columna sirve para especificar el comportamiento a
//   adoptar en el momento de procesar esta opción: cuando la
//   opción es obligatoria, deberá activarse OPT_MANDATORY.
//
// Además, la última entrada de la tabla debe contener todos sus
// elementos nulos, para indicar el final de la misma.
//

//**************** Elementos globales ******************//
static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "f", "forward-op","fft",opt_forward_op, OPT_DEFAULT},
	{1, "r", "reverse-op","ifft",opt_reverse_op, OPT_DEFAULT},
	{1, "b", "block-shift","0",opt_block_shift, OPT_DEFAULT},
	{1, "t", "taps","1",opt_taps, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;		// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)
static ft_flag_t ft_flag;	// Flag of Computing Method
static ift_flag_t ift_flag;	// Syntesis Method
static size_t s_length;		// Size of the Block Shift
static vector<complejo> taps;	// Vector with the EQ coeficients

#define POS_I_OPT 0
#define POS_O_OPT 1
#define POS_F_OPT 2
#define POS_R_OPT 3
#define POS_B_OPT 4
#define POS_T_OPT 5
#define POS_HELP_OPT 6



//*****************************************************//

static void
opt_input(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la entrada
	// estándar. De lo contrario, abrimos un archivo en modo
	// de lectura.
	//
	if (arg == (options+POS_I_OPT)->def_value) {
		iss = &cin;		// Establezco la entrada estandar cin como flujo de entrada
	}
	else {
		ifs.open(arg.c_str(), ios::in); // c_str(): Returns a pointer to an array that contains a null-terminated
										// sequence of characters (i.e., a C-string) representing
										// the current value of the string object.
		iss = &ifs;
	}

	// Verificamos que el stream este OK.
	//
	if (!iss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void
opt_output(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la salida
	// estándar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	//
	if (arg == (options+POS_O_OPT)->def_value) {
		oss = &cout;	// Establezco la salida estandar cout como flujo de salida
	} 
	else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}

	// Verificamos que el stream este OK.
	//
	if (!oss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);		// EXIT: Terminación del programa en su totalidad
	}
}

static void
opt_forward_op(string const &arg)
{
	istringstream iss(arg);
	string aux;
	size_t i;

	// Se verifica que se pueda leer el argumento
	if(!(iss >> aux) || !iss.eof()) {
		cerr << "non-string argument: "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}

	if (iss.bad()) {
		cerr << "cannot read forward-op."
		     << endl;
		exit(1);
	}

	// Innecesario pero sólo lo pongo para chequear
	if (arg == (options+POS_F_OPT)->def_value) {
		ft_flag=FT_FLAG_FFT;	
	} 
	
	else { 
		for(i=0; i<AMOUNT_OF_F_METHODS; i++){
			if(FT_FLAGS[i]==aux){
				ft_flag= static_cast<ft_flag_t>(i);
				break;
			}
		}

		if(i==AMOUNT_OF_F_METHODS){
			cerr << "invalid ft method: "
			     << arg
			     << "."
			     << endl;
			exit(1);
		}
	}
}

static void
opt_reverse_op(string const &arg)
{
	istringstream iss(arg);
	string aux;
	size_t i;

	if(!(iss >> aux) || !iss.eof()) {
		cerr << "non-string argument: "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}

	if (iss.bad()) {
		cerr << "cannot read reverse-op."
		     << endl;
		exit(1);
	}


	// Innecesario pero sólo lo pongo para chequear
	if (arg == (options+POS_R_OPT)->def_value) {
		ift_flag=IFT_FLAG_IFFT;	
	} 
	
	else { 
		for(i=0; i<AMOUNT_OF_R_METHODS; i++){
			if(IFT_FLAGS[i]==aux){
				ift_flag= static_cast<ift_flag_t> (i);
				break;
			}
		}

		if(i==AMOUNT_OF_R_METHODS){
			cerr << "invalid ift method: "
			     << arg
			     << "."
			     << endl;
			exit(1);
		}
	}
}

static void
opt_block_shift(string const &arg)
{
	istringstream iss(arg);
	int aux;

	// Se extrae el 's' de la línea de comandos.
	// Para detectar argumentos que únicamente consistan de
	// números enteros positivos, se verifica que EOF llegue
	// justo después de la lectura exitosa del escalar.
	// A traves del uso de un 'int' auxiliar, se verifica el signo
	
	if(!(iss >> aux) || !iss.eof() || aux<0) {
		cerr << "non-positive integer number: "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}

	if (iss.bad()) {
		cerr << "cannot read block-shift number."
		     << endl;
		exit(1);
	}

	s_length=aux;
}

static void
opt_taps(string const &arg)
{
	size_t i;
	fstream aux_fs;
	complejo aux_c;

	// Si el nombre argumento es igual al argumento por
	// defecto, entonces se crea un vector unitario de
	// longitud 'pow(2,s_length)'.
	//
	if (arg == (options+POS_T_OPT)->def_value) {
		taps.resize(pow(2,s_length));
		for(i=0; i<taps.size(); i++)
			taps[i]=1;
	} 

	// De lo contrario, se requiere que el argumento sea
	// un archivo que contenga los 'pow(2,s_length)'
	// coeficientes necesarios y se crea dicho vector.
	//
	else {
		aux_fs.open(arg.c_str(), ios::in);
		taps.resize(pow(2,s_length));

		for(i=0; i<taps.size(); i++){
			if(!(aux_fs >> aux_c) || aux_fs.eof()){
				cerr << "cannot read taps file "
				     << arg
				     << "."
				     << endl;
				exit(1);
			}
			else
				taps[i]=aux_c;
		}
	}

	// Verificamos que el stream este OK.
	//
	if (!aux_fs.good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);		// EXIT: Terminación del programa en su totalidad
	}
}

static void
opt_help(string const &arg)
{
	cout << "tp1 [-i file] [-o file] [-f ft_method] [-r ift_method] [-b block-shift] [-t taps]"
	     << endl;
	exit(0);
}

	

int
main(int argc, char * const argv[])
{
	cmdline cmdl(options);	// Objeto con parametro tipo option_t (struct) declarado globalmente.
	cmdl.parse(argc, argv);	// Metodo de parseo de la clase cmdline
	proc(iss, oss, s_length, taps, ft_flag, ift_flag);		// Procesamiento de la señal
}
