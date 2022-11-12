#include "stdio.h"
#include "stdlib.h" // u� nev�m kteer� knihovna je ta spr�vn�, dal bych tam v�echny...
#include "string.h"

void nacti(FILE* fp, int grid[4][4])
{
    char* sp; // na rozd�len� ��dku na jednotliv� ��sla
    int y = 0, x = 0; // indexy ��dk� a sloupc�

    if (fp == NULL) // kontrola dojeb�n� se
    {
        printf("\n Nepovedlo se otevrit soubor");
        exit(0);
    }

    char line[100]; // m�sto pro ulo�en� jednoho ��dku tabulky

    y = 0; // vynulov�n� indexu ��dku

    while (fgets(line, 100, fp) != NULL)
    {
        x = 0; // vynulov�n� indexu sloupce

        sp = strtok(line, ";"); //odd�l� z ��dku ��st textu po prvn� ; (prvn� ��slo)
        grid[y][x] = atoi(sp);
        x++;

        sp = strtok(NULL, ";"); // u dal��ch je NULL, pokra�uje kde skon�il
        grid[y][x] = atoi(sp);
        x++;

        sp = strtok(NULL, ";");
        grid[y][x] = atoi(sp);
        x++;

        sp = strtok(NULL, ";");
        grid[y][x] = atoi(sp);
        x++;

        y++; // posune se o ��dek dol�
    }
    fclose(fp);
}

void zapis(FILE* fp, int grid[4][4]) // zapise vysledky posunu do souboru
{
    for (int y = 0; y < 4; y++)
    {
        fprintf(fp, "%i;%i;%i;%i\n", grid[y][0], grid[y][1], grid[y][2], grid[y][3]);
        if (ferror(fp))
        {
            printf("Chyba pri psani do souboru \n");
            break;
        }
    }
    fclose(fp);
}

void vytvor_grid(FILE* fp) // vytvo�� nov� grid s 0 pro novou hru
{
    fp = fopen("grid.csv", "w");
    for (int i = 0; i < 4; i++)
    {
        fprintf(fp, "%i;%i;%i;%i", 0, 0, 0, 0);
        if (i != 3)
            fprintf(fp, "\n");
    }
    fclose(fp);
}