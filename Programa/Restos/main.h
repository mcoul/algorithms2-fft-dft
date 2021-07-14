#ifndef _MAIN_H_INCLUDED_
#define _MAIN_H_INCLUDED_

#include <string>
#include <vector>

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

#endif
