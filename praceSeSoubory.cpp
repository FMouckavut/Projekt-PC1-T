#include "praceSeSoubory.h"

struct stat {
    char name[50];
    int skore;
};

void nacti(FILE* fp, int grid[5][4], int* score)
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
    *score = grid[4][0];
    fclose(fp);
}

void zapis(FILE* fp, int grid[5][4], int* score) // zapise vysledky posunu do souboru
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

void stats(FILE* st) {

    if (st == NULL) {
        st = fopen("statistiky.txt", "w");
    }

    int skore;
    char name[50];
    system("cls");
    for (int i = 0; i < 10; i++) {
        int helpme;
        helpme = fscanf(st, "%d %s", &skore, &name);
        if (helpme == 2) {
            printf("%d %s\n", skore, name);
        }
        else if (helpme == -1) {
            break;
        }
    }


}
// helpme = fscanf(st, "%d %s", &((scoreboard[i]).skore), &((scoreboard[i]).name));