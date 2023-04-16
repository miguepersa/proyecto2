OBJ = main.o Funciones.o
CFLAGS = -Wall -ansi -g
CC = gcc

fameChecker: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

Funciones.o: Funciones.c
	$(CC) $(CFLAGS) -c $^ -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf *.o fameChecker