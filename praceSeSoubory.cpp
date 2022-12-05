#include "praceSeSoubory.h"

struct stat {
    char name[50];
    int skore,z,w;
};

void nacti(FILE* fp, int grid[6][4], int* score)
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

void zapis(FILE* fp, int grid[6][4], int* score, char jmeno[50]) // zapise vysledky posunu do souboru
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
    fprintf(fp, "%i;0;0;0\n", *score);
    fprintf(fp, "%s;0;0;0\n", jmeno);
    fclose(fp);
}

void stats_read(FILE* st) {

    if (st == NULL) {
        return;
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


void stats_edit(FILE* st, int inp_skore, char inp_name[50]) {
    if (st == NULL) {
        st = fopen("statistiky.txt", "w");
        fprintf(st, "%d %s\n", 400, "pan_strik");
        fprintf(st, "%d %s\n", 300, "hobas");
        fprintf(st, "%d %s\n", 200, "joe_biden");
        fclose(st);
        st = fopen("statistiky.txt", "r");
    }

    struct stat scoreboard[10];
    int index = 9;

    
    
    for (int i = 0; i != 10; i++) {
        int helper = fscanf(st, "%d %s", &((scoreboard[i]).skore), &((scoreboard[i]).name));
        if (helper == -1) {
            index = i;
            break;
        }
    }

    for (int i = index; i != -1; i--) {
        if (scoreboard[i].skore > inp_skore && i !=9) {
            for (int j = index; j != i; j--) {
                scoreboard[j].skore = scoreboard[j - 1].skore;
                strcpy(scoreboard[j].name, scoreboard[j - 1].name);
            }
            scoreboard[i+1].skore = inp_skore;
            strcpy(scoreboard[i+1].name, inp_name);
            break;
        }

    }
    
    fclose(st);

    st = fopen("statistiky.txt", "w");

    if (index < 9) {
        index++;
    }

    for (int i = 0; i != index; i++) {
        fprintf(st, "%d %s\n", scoreboard[i].skore, scoreboard[i].name);
    }
    fclose(st);

}
