#include <stdio.h>
#include <time.h>

#include "sudoku.h"
#include "util.h"
#include "grader.h"


#define HINT_NB 17
#define LOOP_NB 5


int main()
{
    srand((unsigned int) time(NULL));
    
    Sudoku s;
    initSudoku(&s); // Remplir la grille avec la grille prédéfinie

    printf("Grille Sudoku initiale :\n");
    printSudoku(s);
    printAsString(s);

    float score = 0;
    int grade = 0;
    gradeSudoku(&s, &score, grade, HINT_NB);
    printf("Score: %f", score);
    printSudoku(s);
    printCandidates(&s);

    return 0;
}

void gradeSudokuMain()
{
    Sudoku s;
    initSudoku(&s); // Remplir la grille avec la grille prédéfinie

    printf("Grille Sudoku initiale :\n");
    printSudoku(s);
    printAsString(s);

    float score = 0;
    int grade = 0;
    gradeSudoku(&s, &score, grade, HINT_NB);
    printf("Score: %f", score);
    printSudoku(s);
    printCandidates(&s);
}

void generateSudoku()
{
    float mean = 0;
    Sudoku s;

    for (int i = 0; i < LOOP_NB; i++)
    {
        clock_t startTime = clock();
        s = createPuzzle(HINT_NB);
        clock_t endTime = clock();
        float score = 0;
        printf("score: %f \n", score);
        printf("sudoku: ");
        printAsString(s);
        mean += (float)(endTime - startTime) / CLOCKS_PER_SEC;
    }

    //printf("Last sudoku generated: \n");
    //printAsString(s);
    //printSudoku(s);
    printf("Average time taken: %f", mean / LOOP_NB);
}