CC     = gcc
CFLAGS = -Wall -Wextra -std=c99
LIBS   = -lm
OBJ    = main.o artemis.o validaciones.o

artemis: $(OBJ)
	$(CC) $(CFLAGS) -o artemis $(OBJ) $(LIBS)

main.o: main.c artemis.h validaciones.h
	$(CC) $(CFLAGS) -c main.c

artemis.o: artemis.c artemis.h
	$(CC) $(CFLAGS) -c artemis.c

validaciones.o: validaciones.c validaciones.h
	$(CC) $(CFLAGS) -c validaciones.c

clean:
	rm -f *.o artemis
