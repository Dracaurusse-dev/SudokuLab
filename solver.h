#ifndef SOLVER_H
#define SOLVER_H

#include "sudoku.h"
#include "util.h"

void solveSudoku(Sudoku* s);
int backtracking(Cell grid[9][9], int row, int col);

#endif // SOLVER_H
