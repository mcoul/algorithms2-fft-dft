# Makefile para compilar el Trabajo Práctico 1 de Algoritmos y Programación II

DIR_INCLUDE= -I.
CXX = g++
CXXARGS  = -ansi -pedantic -Wall -g
CXXFLAGS = $(DIR_INCLUDE) $(CXXARGS)
TEST_DIFF = diff -b
RM = -rm -f


all: tp1.exe 
	
tp1.exe: main.o cmdline.o complejo.o ft.o proc.o cmdline.h complejo.h ft.h proc.h 
	$(CXX) $(CXXFLAGS) -o tp1.exe main.o cmdline.o complejo.o ft.o proc.o


# Declaración de targets de objetos para tp1
main.o: main.cc
	$(CXX) $(CXXFLAGS) -c -o main.o main.cc
main.cc: cmdline.h complejo.h ft.h proc.h 

cmdline.o: cmdline.cc
	$(CXX) $(CXXFLAGS) -c -o cmdline.o cmdline.cc
cmdline.cc: cmdline.h

complejo.o: complejo.cc
	$(CXX) $(CXXFLAGS) -c -o complejo.o complejo.cc
complejo.cc: complejo.h

ft.o: ft.cc
	$(CXX) $(CXXFLAGS) -c -o ft.o ft.cc
ft.cc: ft.h

proc.o: proc.cc
	$(CXX) $(CXXFLAGS) -c -o proc.o proc.cc
proc.cc: proc.h complejo.h ft.h

### Testing
test: tp1.exe test1 test2 test3 test4 test5 test6 test-valgrind 

# Empty file test
test1:
	@set -e; echo **TEST 1** - Empty file;		\
	touch test1.in;					\
	./tp1.exe -i test1.in -o test1.out;		\
	if ($(TEST_DIFF) test1.out test1.in); 		\
	then	echo **TEST 1 OK**;			\
	else	echo **TEST 1 FAILED**;			\
	fi											
	@rm test1.*;			

# Filling with ceros test
test2:
	@set -e; echo **TEST 2** - Filling with ceros;\
	echo 1 1 > test2.in;\
	echo \(1,0\) \(1,0\) \(0,0\) \(0,0\) > test2.t;\
	./tp1.exe -i test2.in -o test2.out -b 2;\
	if ($(TEST_DIFF) test2.out test2.t);\
	then	echo **TEST 2 OK**;\
	else	echo **TEST 2 FAILED**;				\
	fi											
	@rm test2.*;			

# Real input test 
test3:
	@set -e; echo **TEST 3** - Real input;			\
	echo 1 1 1 1 > test3.in;				\
	echo \(1,0\) \(1,0\) \(1,0\) \(1,0\) > test3.ref;		\
	./tp1.exe -i test3.in -o test3.out -b 2;		\
	if ($(TEST_DIFF) test3.out test3.ref);			\
	then	echo **TEST 3 OK**;				\
	else	echo **TEST 3 FAILED**;				\
	fi
	@rm test3.*;

# Complex input test
test4:
	@set -e; echo **TEST 4** - Complex input;		\
	echo \(1,0\) \(0,9\) \(0,0\) \(1,1\)> test4.in;		\
	echo \(1,0\) \(0,9\) \(0,0\) \(1,1\)> test4.ref;		\
	./tp1.exe -i test4.in -o test4.out -b 2;		\
	if ($(TEST_DIFF) test4.out test4.ref);			\
	then	echo **TEST 4 OK**;				\
	else	echo **TEST 4 FAILED**;				\
	fi
	@rm test4.*;

# Checking method by checking output
test5:
	@set -e; echo **TEST 5** - Checking methods by checking outputs; \
	echo 1 1 1 0 > test5.in;	\
	echo \(1,0\) \(1,0\) \(1,0\) \(0,0\) > test5.ref; \
	./tp1.exe -i test5.in -o test5_1.out;			\
	./tp1.exe -i test5.in -o test5_2.out -f dft;		\
	./tp1.exe -i test5.in -o test5_3.out -f fft -r idft;	\
	./tp1.exe -i test5.in -o test5_4.out -f dft -r ifft;	\
	./tp1.exe -i test5.in -o test5_5.out -f dft -r idft;	\
	if (!($(TEST_DIFF) test5_1.out test5.ref));			\
	then	echo **TEST 5 FAILED**;				\
	elif (!($(TEST_DIFF) test5_2.out test5.ref));		\
	then 	echo **TEST 5 FAILED**;				\
	elif (!($(TEST_DIFF) test5_3.out test5.ref));		\
	then	echo **TEST 5 FAILED**;				\
	elif (!($(TEST_DIFF) test5_4.out test5.ref));		\
	then	echo **TEST 5 FAILED**;				\
	elif (!($(TEST_DIFF) test5_5.out test5.ref));		\
	then	echo **TEST 5 FAILED**;				\
	else	echo **TEST 5 OK**;				\
	fi
	@rm test5*;


# Checking taps
test6:
	@set -e; echo **TEST 6** - Checking taps;		\
	echo 2 2 2 2 > coeficientes4.txt;			\
	echo 1 2 3 \(0,4\) 5 6 7 0 > test6.in;			\
	echo \(2,0\) \(4,0\) \(6,0\) \(0,8\) \(10,0\) \(12,0\) \(14,0\) \(0,0\) > test6.ref; \
	./tp1.exe -i test6.in -o test6.out -b 2 -t coeficientes4.txt; \
	if ($(TEST_DIFF) test6.out test6.ref);			\
	then	echo **TEST 6 OK**;				\
	else	echo **TEST 6 FAILED**;				\
	fi
	@rm test6.* coeficientes4.txt;

# Memory test with Valgrind
test-valgrind:
	@set -e; echo **TEST VALGRIND** - Memory check;		\
	echo 1 2 3 4 > test-valgrind.in;			\
	echo \(1,0\) \(2,0\) \(3,0\) \(4,0\) > test-valgrind.ref; \
	valgrind --tool=memcheck ./tp1.exe < test-valgrind.in > test-valgrind.out 2>/dev/null;	\
       	if ($(TEST_DIFF) test-valgrind.ref test-valgrind.out >/dev/null 2>&1) \
	then	echo **TEST VALGRIND OK**;	\
	else	echo **TEST VALGRIND FAILED**;	\
	fi
	@rm test-valgrind*;

################## END TESTING #######################



# Cleaning targets

.PHONY: clean
clean:
	$(RM) -v *.o *.exe *.t *.out *.err .*.swp

.PHONY: partial_cleaning
partial_cleaning:
	$(RM) *.o .*.swp	
