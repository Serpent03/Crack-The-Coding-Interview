cc = gcc
flags = -Wall -g -c
bash = bash -c

main: libCITC.a lib.c
	$(cc) -o main ./lib.o ./main.c -L -lCITC

libCITC.a: lib.c lib.h
	$(cc) $(flags) lib.c
	$(bash) "ar -rcs libCITC.a *.o"

clean:
	$(bash) "rm *.o ; rm *.a; clear"
