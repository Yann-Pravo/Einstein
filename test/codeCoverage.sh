#!/bin/bash

make clean
make
./testsRunner
gcov -o ../src/source/ Graph.c 
gcov -o ../src/source/ City.c
gcov -o ../src/source/ ParseFile.c
gcov -o ../src/source/ ExportMap.c
rm -rf ./*.gcno ./*.gcda ../*.gcno ../*.gcda ../src/source/*.gcno ../src/source/*.gcda
make clean
