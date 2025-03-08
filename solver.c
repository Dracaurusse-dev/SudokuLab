#include "solver.h"
#include "sudoku.h"
#include "util.h"

#include <stdio.h>


void solveSudoku(Sudoku* s)
{
	int worked = backtracking(s->grid, 0, 0);
    if (!worked)
    {
        printf("Sudoku seem to have no solution");
    }
}


int backtracking(Cell grid[9][9], int row, int col)
{
    if (row == GRID_SIZE) 
    {
        return 1;
    }

    if (col == GRID_SIZE) 
    {
        return backtracking(grid, row + 1, 0);
    }

    if (grid[row][col].value != 0) 
    {
        return backtracking(grid, row, col + 1);
    }

    for (int num = 1; num <= GRID_SIZE; num++) 
    {
        grid[row][col].value = num;
        if (isValidPlacement(grid, row, col)) 
        {
            if (backtracking(grid, row, col + 1)) 
            {
                return 1;
            }
        }
        grid[row][col].value = 0;
    }

    return 0;
}