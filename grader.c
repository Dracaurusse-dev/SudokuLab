#include "grader.h"
#include "sudoku.h"
#include "util.h"

#include <stdio.h>
#include <math.h>

#define MAX_ITER 50

void gradeSudoku(Sudoku* s, float* score, int grade, int defaultHints)
{
	// grade is an int and is converted with a switch statement
	if (*score < 0) *score = 0;
    int count = 0;

    while (!isComplete(*s) && count < MAX_ITER)
    {
        updateCandidates(s);
        putPossibleCand(s, score);
        // TODO: add other techs and test if they are done
        count++;
    }

}


int isCandidateValid(Sudoku* s, int row, int col, int candidate)
{
    int temp = s->grid[row][col].value;
    s->grid[row][col].value = candidate;
    if (!isValidPlacement(s->grid, row, col))
    {
        s->grid[row][col].value = temp;
        return 0;
    }

    s->grid[row][col].value = temp;
    return 1; 
}


void updateCandidates(Sudoku* s) 
{
    for (int i = 0; i < GRID_SIZE; i++) 
    {
        for (int j = 0; j < GRID_SIZE; j++) 
        {
            if (s->grid[i][j].value != 0) 
            {
                for (int k = 0; k < GRID_SIZE; k++)
                {
                    s->grid[i][j].candidates[k] = 0;
                }
            }
            else
            {
                for (int k = 0; k < GRID_SIZE; k++)
                {
                    int candidate = s->grid[i][j].candidates[k];

                    if (candidate != 0 && !isCandidateValid(s, i, j, candidate))
                    {
                        // Si le candidat n'est pas valide, on le supprime de la liste
                        s->grid[i][j].candidates[k] = 0;
                    }
                }
            }
            s->grid[i][j].candidates[0] = 0;
        }
    }
}



void putPossibleCand(Sudoku* s, int* score) 
{
    for (int i = 0; i < GRID_SIZE; i++) 
    {
        for (int j = 0; j < GRID_SIZE; j++) 
        {
            int count = 0;
            int lastVal = 0;

            for (int k = 0; k < GRID_SIZE; k++) 
            {
                if (s->grid[i][j].candidates[k] != 0) 
                {
                    count++;
                    lastVal = s->grid[i][j].candidates[k];
                }

                if (count > 1) break;
            }

            if (count == 1) 
            {
                s->grid[i][j].value = lastVal;
                *score += 1;
            }
        }
    }
}


////////////////////////////////////////////
// Non human part
////////////////////////////////////////////

void nonHumanAlgo(Sudoku s, float* score, int grade, int defaultHints)
{
    *score = (float) sqrt(defaultHints / getAverageHint(s)) + (float) tgamma(getAverageCand(s) / SIZE_1D) + (float) fabs(getConflicts(s) - log(getEmptyCells(s)));
}

float getAverageHint(Sudoku s)
{
    float sum = 0.0;
    int count = 0;

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (s.grid[i][j].value != 0) 
            {
                sum += (float) s.grid[i][j].value; 
                count++; 
            }
        }
    }

    return (count > 0) ? (sum / (float) count) : 0.0;
}

float getAverageCand(Sudoku s)
{
    float sum = 0.0;
    int count = 0;

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (s.grid[i][j].value == 0) // Seulement si la case est vide
            {
                sum += (float) countCandidates(s.grid[i][j]); // Nombre de candidats pour cette case
                count++;
            }
        }
    }

    return (count > 0) ? (sum / count) : 0.0;
}

int countCandidates(Cell cell)
{
    int count = 0;
    for (int k = 0; k < GRID_SIZE; k++)
    {
        if (cell.candidates[k] != 0)
        {
            count++;
        }
    }
    return count;
}

int getConflicts(Sudoku s)
{
    int conflicts = 0;

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (s.grid[i][j].value != 0)
            {
                for (int k = 0; k < GRID_SIZE; k++)
                {
                    if (k != j && s.grid[i][k].value == s.grid[i][j].value)
                        conflicts++;
                }

                for (int k = 0; k < GRID_SIZE; k++)
                {
                    if (k != i && s.grid[k][j].value == s.grid[i][j].value)
                        conflicts++;
                }

                int boxRowStart = (i / 3) * 3;
                int boxColStart = (j / 3) * 3;
                for (int r = boxRowStart; r < boxRowStart + 3; r++)
                {
                    for (int c = boxColStart; c < boxColStart + 3; c++)
                    {
                        if (r != i && c != j && s.grid[r][c].value == s.grid[i][j].value)
                            conflicts++;
                    }
                }
            }
        }
    }

    return conflicts;
}

int getEmptyCells(Sudoku s)
{
    int emptyCells = 0;
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (s.grid[i][j].value == 0)
                emptyCells++;
        }
    }

    return emptyCells;
}

void printCandidates(Sudoku* s) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (s->grid[i][j].value == 0) {
                printf("Cell[%d][%d] candidates: ", i, j);
                for (int k = 0; k < GRID_SIZE; k++) {
                    if (s->grid[i][j].candidates[k] != 0) {
                        printf("%d ", s->grid[i][j].candidates[k]);
                    }
                }
                printf("\n");
            }
        }
    }
}
