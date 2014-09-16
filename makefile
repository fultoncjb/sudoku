# sudoku makefile

CC = g++
LINK_OPTION = -lz
COMPILE_OPTION = -g

all: sudoku

clean:
	rm -f *.o *.out sudoku

sudoku: sudoku.cpp sudoku.h 
	${CC} ${COMPILE_OPTION} sudoku.cpp -o sudoku



