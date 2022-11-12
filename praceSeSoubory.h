#pragma once
#include "stdio.h"
#include "stdlib.h" // už nevím kteerá knihovna je ta správná, dal bych tam všechny...
#include "string.h"

void nacti(FILE* fp, int grid[4][4]);
void zapis(FILE* fp, int grid[4][4]);
void vytvor_grid(FILE* fp);