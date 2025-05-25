all: main

main: main.o salao.o cozinha.o
	gcc -o main main.o salao.o cozinha.o 

main.o: main.c
	gcc -c main.c

salao.o: salao.c salao.h
	gcc -c salao.c

cozinha.o: cozinha.c cozinha.h
	gcc -c cozinha.c

test: main
    ./main

clean:
	rm -f main *.o 
