#ifndef GRADER_H
#define GRADER_H

#include "sudoku.h"

void gradeSudoku(Sudoku* s, float* score, int grade, int defaultHints);

void updateCandidates(Sudoku* s);
int isCandidateValid(Cell grid[GRID_SIZE][GRID_SIZE], int i, int j, int candidate);
void putPossibleCand(Sudoku* s, int* score);
void printCandidates(Sudoku* s);

void nonHumanAlgo(Sudoku s, float* score, int grade, int defaultHints);
float getAverageHint(Sudoku s);
float getAverageCand(Sudoku s);
int countCandidates(Cell cell);
int getConflicts(Sudoku s);
int getEmptyCells(Sudoku s);

#endif  // GRADER_H
