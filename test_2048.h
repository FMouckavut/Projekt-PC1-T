// test_2048.h: Soubor k zahrnutí pro standardní systémové soubory k zahrnutí
// nebo soubory k zahrnutí specifické pro projekt.

#pragma once

#include <iostream>
#include "stdio.h"
#include "stdlib.h" 
#include "string.h"
#include "time.h"
#include "conio.h" //getch()

int grid[4][4] = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} };

void rnd_gen(int grid[4][4]);
int Down(int grid[4][4]);
int Up(int grid[4][4]);
int Left(int grid[4][4]);
int Right(int grid[4][4]);
void Action(int ch);
void hra();


int score = 0;
FILE* fp;
FILE* st;