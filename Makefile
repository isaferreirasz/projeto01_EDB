//nao ta pronto ainda falta a parte da cozinha (imagino que talvez se chama cozinha.c)
all: main

main: main.c salao.c cozinha.c
	gcc main.c salao.c cozinha.c -o main

clean:
	rm -f *.o main
