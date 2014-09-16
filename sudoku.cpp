#include "sudoku.h"

using namespace std;

int main()
{
	sudoku puzzle;
	puzzle.SolvePuzzle();

	return 0;
}

sudoku::sudoku()
{
	// Initialize the grid
	std::string filename = "custom261.txt";
	setClusters = 0;
	node::coord curCoord = {0,0};

	// Read in file stream
	ifstream inputGridFile(filename.c_str());
	if( inputGridFile.is_open() )
	{
		string s;
		string value;
		
		while(getline(inputGridFile,s))
		{
			stringstream ss(s);
			while( getline(ss,value,',') )
			{
				m_grid[curCoord.y][curCoord.x].value = atoi(value.c_str());
				if( atoi(value.c_str()) != 0 )
					m_grid[curCoord.y][curCoord.x].set = true;
				curCoord.x++;
				if(curCoord.x > 8)
				{
					curCoord.x = 0;
					curCoord.y++;
				}
			}
		}	
	}
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

	printPuzzle();
	
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

	for(unsigned int ii=1;ii<=9;ii++)
	{
		if(checkValidCluster(r,c,ii) &&
		   checkValidRow(r,c,ii) &&
		   checkValidColumn(r,c,ii)
		  )
		{
			m_grid[r][c].value = ii;
			if( RecursiveSolver(r,c) )
				return true;
			else
				m_grid[r][c].value = 0;

		}

		//m_grid[r][c].value = 0;
	}

	//printPuzzle();

	//m_grid[r][c].value = 0;

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
	
