#include "util.h"

#include <stdlib.h>


void shuffle(int* array, int size)
{
    for (int i = 0; i < size; i++) 
    {
        int j = rand() % (i + 1);
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}

