#pragma once
#include "stdio.h"
#include "stdlib.h" // u� nev�m kteer� knihovna je ta spr�vn�, dal bych tam v�echny...
#include "string.h"

void nacti(FILE* fp, int grid[5][4], int* score);
void zapis(FILE* fp, int grid[5][4], int* score);
void stats(FILE* st);
