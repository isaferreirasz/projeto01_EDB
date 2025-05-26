all: main

main: arquivos.c/main.o arquivos.c/salao.o arquivos.c/cozinha.o
	gcc -o main arquivos.c/main.o arquivos.c/salao.o arquivos.c/cozinha.o

arquivos.c/main.o: arquivos.c/main.c
	gcc -c arquivos.c/main.c -o arquivos.c/main.o -Iarquivos.h

arquivos.c/salao.o: arquivos.c/salao.c arquivos.h/salao.h
	gcc -c arquivos.c/salao.c -o arquivos.c/salao.o -Iarquivos.h

arquivos.c/cozinha.o: arquivos.c/cozinha.c arquivos.h/cozinha.h
	gcc -c arquivos.c/cozinha.c -o arquivos.c/cozinha.o -Iarquivos.h

test: main
	./main

clean:
	rm -f main arquivos.c/*.o
