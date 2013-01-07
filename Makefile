CC = gcc
CFLAGS = -Wall -lm -O3

OBJS = ./src/source/City.o ./src/source/Graph.o ./src/source/Einstein.o ./src/source/ParseFile.c ./src/source/ExportMap.c

all: einstein 

einstein: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o ./src/source/*.o *.gcda *.gcno ./src/source/*.gcda ./src/source/*.gcno

superclean: all clean

