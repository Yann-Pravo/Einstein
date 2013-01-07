CC ?= gcc
CFLAGS = -Wall -fprofile-arcs -ftest-coverage -lm
LDFLAGS = -Lcu/ -lcu

OBJS = testParseFile.o testGraph.o testExportMap.o testCity.o testsRunner.o ../src/source/ExportMap.o ../src/source/City.o ../src/source/ParseFile.o ../src/source/Graph.o

all: testsRunner

testsRunner: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o ../src/source/*.o

.PHONY: clean all clean
