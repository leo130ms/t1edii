#makefile

all: trab1

trab1: main.o kruskal.o Matriz.o Ponto.o Union.o
	gcc -o trab1 main.o kruskal.o Matriz.o Ponto.o Union.o -lm

main.o: main.c
	gcc -c main.c

kruskal.o: kruskal.c
	gcc -c kruskal.c

Matriz.o: Matriz.c
	gcc -c Matriz.c

Ponto.o: Ponto.c
	gcc -c Ponto.c

Union.o: Union.c
	gcc -c Union.c

clean:
	rm -rf *.o