#include "sudoku.h"
#include "util.h"
#include "solver.h"

#include <stdio.h>


Sudoku createPuzzle(int hints)
{
	Sudoku s;

	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			s.grid[i][j].value = 0;
			for (int k = 0; k < GRID_SIZE; k++)
			{
				s.grid[i][j].candidates[k] = k + 1;
			}
		}
	}

	// put 11 random numbers in the grid and make sure they are valid
	int positions[SIZE_1D];
	for (int i = 0; i < SIZE_1D; i++)
	{
		positions[i] = i;
	}
	shuffle(positions, SIZE_1D);

	for (int i = 0; i < FIRST_NUMBERS; i++)
	{
		int pos = positions[i];
		int row = pos / GRID_SIZE;
		int col = pos % GRID_SIZE;
		
		s.grid[row][col].value = rand() % GRID_SIZE + 1;

		while (!isValidPlacement(s.grid, row, col))
		{
			s.grid[row][col].value = rand() % GRID_SIZE + 1;
		}
	}

	solveSudoku(&s);


	removeCells(s.grid, positions, SIZE_1D - hints);

	//printSudoku(s);
	//printf("Hints amount: %d", getHintNb(s));
	
	return s;
}


void removeCells(Sudoku* s, int positions[SIZE_1D], int maxRemove)
{
	shuffle(positions, SIZE_1D);

	int removed = 0;
	for (int i = 0; i < SIZE_1D && removed < maxRemove; i++) 
	{

		int pos = positions[i];
		int row = pos / GRID_SIZE;
		int col = pos % GRID_SIZE;

		int temp = s->grid[row][col].value;
		s->grid[row][col].value = 0;

		if (getSolutionCount(s, 0, 0) != 1) 
		{
			s->grid[row][col].value = temp;
		}
		else 
		{
			removed++;
		}
	}
}

int getSolutionCount(Sudoku* s, int row, int col)
{
	if (row == GRID_SIZE)
	{
		return 1;
	}

	if (col == GRID_SIZE)
	{
		return getSolutionCount(s, row + 1, 0);
	}

	if (s->grid[row][col].value != 0)
	{
		return getSolutionCount(s, row, col + 1);
	}

	int count = 0;

	for (int num = 1; num <= GRID_SIZE; num++)
	{
		s->grid[row][col].value = num;

		if (isValidPlacement(s->grid, row, col))
		{
			count += getSolutionCount(s, row, col + 1);
		}

		s->grid[row][col].value = 0; // Annule le choix pour continuer
	}

	return count;
}

/////////////////////////////////////////////
// utility functions
/////////////////////////////////////////////
int isValidPlacement(Cell grid[9][9], int row, int col)
{
	int value = grid[row][col].value;

	int boxRowStart = (row / 3) * 3;
	int boxColStart = (col / 3) * 3;

	for (int i = 0; i < 9; i++)
	{
		// Row logic
		if (grid[row][i].value == value && i != col) return 0;
		
		// Col logic
		if (grid[i][col].value == value && i != row) return 0;
		
		// Box logic
		int r = boxRowStart + i / 3;
		int c = boxColStart + i % 3;

		if (r == row && c == col)
			continue;
		if (grid[r][c].value == value)
			return 0;
	}

	return 1;
}


void printSudoku(Sudoku s)
{
	printf("\n+-------+-------+-------+\n");

	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			if (j % 3 == 0)
				printf("| ");

			printf("%d ", s.grid[i][j].value);
		}

		printf("|\n");
		if ((i + 1) % 3 == 0) 
			printf("+-------+-------+-------+\n");
	}
}


int getHintNb(Sudoku s)
{
	int clues = 0;

	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			if (s.grid[i][j].value != 0) clues++;
		}
	}

	return clues;
}

void printAsString(Sudoku s)
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			int value = s.grid[i][j].value;
			if (value != 0)	printf("%d", value);
			else printf(".");
		}
	}
	printf("\n");
}

int isComplete(Sudoku s)
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			if (s.grid[i][j].value == 0) return 0;
		}
	}

	return 1;
}

void initSudoku(Sudoku* s)
{
	int predefinedGrid[GRID_SIZE][GRID_SIZE] =
	{
		{0, 0, 0, 0, 0, 0, 8, 9, 0},
		{0, 0, 0, 6, 1, 4, 6, 0, 0},
		{0, 4, 0, 0, 2, 0, 0, 0, 2},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 5, 6, 0, 9, 0, 3, 0, 0},
		{0, 3, 0, 0, 1, 0, 5, 3, 0},
		{0, 7, 0, 0, 5, 8, 0, 0, 0},
		{0, 0, 0, 5, 1, 0, 0, 0, 0},
		{2, 6, 0, 4, 0, 0, 0, 0, 0}
	};

	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			s->grid[i][j].value = predefinedGrid[i][j];
			for (int k = 0; k < GRID_SIZE; k++)
			{
				s->grid[i][j].candidates[k] = k + 1;
			}
		}
	}
}