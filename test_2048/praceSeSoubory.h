#pragma once
#include "stdio.h"
#include "stdlib.h" // už nevím kteerá knihovna je ta správná, dal bych tam všechny...
#include "string.h"

void nacti(FILE* fp, int grid[5][4], int *score);
void zapis(FILE* fp, int grid[5][4], int *score);
void vytvor_grid(FILE* fp);