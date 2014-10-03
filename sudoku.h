#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<stdlib.h>
#include "gridwindow.h"

class sudoku
{
	public:
		class node
		{
			public:
				node();
				bool set;
				int value;

				struct coord {
				int x;
				int y;
				};
			protected:	

		};

		sudoku();
		bool initPuzzle(SudokuEntry gridEntries[9][9]);

		bool SolvePuzzle();
		unsigned int setClusters;
		void printPuzzle();
		int getPuzzleValue(int row, int column);
	protected:
		bool checkValidCluster(int r,int c,int value);
		bool checkValidRow(int r,int c,int value);
		bool checkValidColumn(int r,int c,int value);
		bool RecursiveSolver(int r,int c);
		node m_grid[9][9];
};

