#include "sudoku.h"
//#include "gridwindow.h"

using namespace std;

sudoku::sudoku()
{
}

bool sudoku::initPuzzle(SudokuEntry gridEntries[9][9])
{
	std::string valueString = gridEntries[0][0].get_text();
	int value;
	setClusters = 0;

	value = atof(valueString.c_str());

	for(unsigned int ii=0;ii<9;ii++)
	{
		for(unsigned int jj=0;jj<9;jj++)
		{
			valueString = gridEntries[jj][ii].get_text();
			value = atof(valueString.c_str());

			if(value)
			{
				m_grid[ii][jj].value = value;
				m_grid[ii][jj].set = true;
			}
			else
			{
				m_grid[ii][jj].value = 0;
				m_grid[ii][jj].set = false;
			}
		}
	}

	//printPuzzle();

	return true;
}

// Return true if the newly added number is valid within the 3x3 cluster
bool sudoku::checkValidCluster(int r, int c,int value)
{
	// Find what cluster (c,r) is in using int division
	int horiz = c/3;
	int vert = r/3;

	// Check all the nodes in this cluster minus the current one
	for(unsigned int ii=horiz*3;ii<horiz*3+3;ii++)
	{
		for(unsigned int jj=vert*3;jj<vert*3+3;jj++)
		{
			if(ii != c && jj != r && m_grid[jj][ii].value != 0 && m_grid[jj][ii].value == value)
				return false;
		}
	}

	return true;
}

// Return true if the newly added number is valid across the row
bool sudoku::checkValidRow(int r,int c,int value)
{
	for(unsigned int ii=0;ii<9;ii++)
	{
		if(ii != c && m_grid[r][ii].value != 0 && m_grid[r][ii].value == value)
			return false;
	}

	return true;
}

// Return true if the newly added number is valid down the column
bool sudoku::checkValidColumn(int r,int c,int value)
{
	for(unsigned int ii=0;ii<9;ii++)
	{
		if(ii != r && m_grid[ii][c].value != 0 && m_grid[ii][c].value == value)
			return false;
	}

	return true;
}

void sudoku::SolvePuzzle()
{
	RecursiveSolver(0,0);
	
}

bool sudoku::RecursiveSolver(int r,int c)
{

	// Find a node that is not already solved
	while(r <= 8 && m_grid[r][c].value != 0)
	{
		c++;
		if( c > 8  )
		{
			r++;
			c = 0;
		}
	}

	// Done with puzzle
	if (r > 8)
		return true;

	// Try all possible values
	for(unsigned int ii=1;ii<=9;ii++)
	{
		// Check if this value works in puzzle
		if(checkValidCluster(r,c,ii) &&
		   checkValidRow(r,c,ii) &&
		   checkValidColumn(r,c,ii)
		  )
		{
			// Set the value
			m_grid[r][c].value = ii;
			// Check if future recursive solvers return true
			if( RecursiveSolver(r,c) )
				return true;
			// Reset the value			
			else
				m_grid[r][c].value = 0;

		}
	}

	return false;
}

sudoku::node::node()
{
	set = false;
}

void sudoku::printPuzzle()
{
	for(unsigned int ii=0;ii<9;ii++)
	{
		for(unsigned int jj=0;jj<9;jj++)
		{
			cout << m_grid[ii][jj].value << ",";
		}
		cout << endl;
	}
}

int sudoku::getPuzzleValue(int row,int column)
{
	return m_grid[row][column].value;
}


	
