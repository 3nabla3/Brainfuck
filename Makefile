CC=gcc
CFLAGS=-O3 -Wall

brainfuck: main.o
	$(CC) -o brainfuck main.o $(CFLAGS)

main.o: main.c brainfuck.h
	$(CC) -c main.c -o main.o $(CFLAGS)

clean:
	rm -rf *.o brainfuck
