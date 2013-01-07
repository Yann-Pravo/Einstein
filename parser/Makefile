antlr: clean-antlr
	gcc -c -Wall -I/usr/local/include output/*.c
	gcc -c -Wall -I/usr/local/include -I./output main.c
	export LD_LIBRARY_PATH=/usr/local/lib
	gcc -o parser.out *.o -lantlr3c
	rm -f *.o

clean-antlr: clean
	rm -f parser.out

clean:
	rm -f *.o
