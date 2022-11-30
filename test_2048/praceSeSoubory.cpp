#include "stdio.h"
#include "stdlib.h" // už nevím která knihovna je ta správná, dal bych tam všechny...
#include "string.h"

void nacti(FILE* fp, int grid[5][4], int *score)
{
    char* sp; // na rozdìlení øádku na jednotlivá èísla
    int y = 0, x = 0; // indexy øádkù a sloupcù

    if (fp == NULL) // kontrola dojebání se
    {
        printf("\n Nepovedlo se otevrit soubor");
        exit(0);
    }

    char line[100]; // místo pro uložení jednoho øádku tabulky

    y = 0; // vynulování indexu øádku

    while (fgets(line, 100, fp) != NULL)
    {
        x = 0; // vynulování indexu sloupce

        sp = strtok(line, ";"); //oddìlá z øádku èást textu po první ; (první èíslo)
        grid[y][x] = atoi(sp);
        x++;

        sp = strtok(NULL, ";"); // u dalších je NULL, pokraèuje kde skonèil
        grid[y][x] = atoi(sp);
        x++;

        sp = strtok(NULL, ";");
        grid[y][x] = atoi(sp);
        x++;

        sp = strtok(NULL, ";");
        grid[y][x] = atoi(sp);
        x++;

        y++; // posune se o øádek dolù
    }
    *score += grid[4][0]; // poslední øádek se používá jako skóre
    fclose(fp);
}

void zapis(FILE* fp, int grid[5][4], int *score) // zapise vysledky posunu do souboru
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
    fprintf(fp, "%i;0;0;0", *score);
    fclose(fp);
}

void vytvor_grid(FILE* fp) // vytvoøí nový grid s 0 pro novou hru
{
    fp = fopen("grid.txt", "w");
    for (int i = 0; i < 5; i++)
    {
        fprintf(fp, "%i;%i;%i;%i", 0, 0, 0, 0);
        if (i != 4)
            fprintf(fp, "\n");
    }
    fclose(fp);
}