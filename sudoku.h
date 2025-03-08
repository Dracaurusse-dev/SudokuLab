#ifndef SUDOKU_H
#define SUDOKU_H

#define FIRST_NUMBERS 11
#define GRID_SIZE 9
#define SIZE_1D GRID_SIZE * GRID_SIZE


typedef struct
{
	int value;
	int candidates[GRID_SIZE];
} Cell;

typedef struct
{
	Cell grid[GRID_SIZE][GRID_SIZE];
} Sudoku;


Sudoku createPuzzle(int hints);
void removeCells(Sudoku* s, int positions[SIZE_1D], int maxRemove);
int getSolutionCount(Sudoku* s, int row, int col);

void initSudoku(Sudoku* s);

int isValidPlacement(Cell grid[9][9], int row, int col);
int getHintNb(Sudoku s);
void printSudoku(Sudoku s);
//void getString(Sudoku s);
void printAsString(Sudoku s);
int isComplete(Sudoku s);

#endif // SUDOKU_H