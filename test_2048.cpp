#include "test_2048.h"
#include "praceSeSoubory.h"


void rnd_gen(int grid[4][4]) { // vytvoří nová čísla po posunutí
    int bul = 0;
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            if (grid[x][y] == 0) {
                bul = 1;
            }
        }
    }

    if (!(bul)) {
        return;
    }

    while (1) {
        int x = rand() % 4;
        int y = rand() % 4;
        if (grid[x][y] == 0) {
            grid[x][y] = ((rand() % 2) + 1) * 2;
            score += grid[x][y];
            break;
        }
    }

}

void Action(int ch)
{
    if (ch == 224)
    { // přečte první vstup ze šipky, vždycky 224
        switch (getch())
        { // vezme druhý vstup, kód jednotlivé šipky
        case 72:
            Up(grid);
            rnd_gen(grid);
            break;
        case 80:
            Down(grid);
            rnd_gen(grid);
            break;
        case 77:
            Right(grid);
            rnd_gen(grid);
            break;
        case 75:
            Left(grid);
            rnd_gen(grid);
            break;
        default:
            break;
        }
    }
 
}

int Down(int grid[4][4])
{
    
    int test = 0;
    for (int i = 3; i != -1; i--) {
        int last_used = 0;
        for (int j = 3; j != -1; j--) {
            if (grid[i][j] != 0) {
                int pohyb = 1;
                int moved_digit = grid[i][j];
                while (i != 3 && grid[i + pohyb][j] == 0 && (i + pohyb) != 4) {
                    grid[i + pohyb][j] = moved_digit;
                    grid[i + pohyb - 1][j] = 0;
                    pohyb++;
                    test = 1;
                }

                pohyb--;


                if (i != 3 && grid[i + pohyb][j] == grid[i + 1 + pohyb][j] && grid[i + pohyb][j] != last_used) {
                    grid[i + pohyb + 1][j] *= 2;
                    last_used = grid[i + pohyb + 1][j];
                    grid[i + pohyb][j] = 0;
                    test = 1;
                }
            }
        }
    }
    return test;
}

int Up(int grid[4][4])
{
    
    int test = 0;
    for (int i = 0; i != 4; i++) {
        int last_used = 0;
        for (int j = 0; j != 4; j++) {
            if (grid[i][j] != 0) {
                int pohyb = 1;
                int moved_digit = grid[i][j];
                while (i != 0 && grid[i - pohyb][j] == 0 && i - pohyb != -1) {
                    grid[i - pohyb][j] = moved_digit;
                    grid[i - pohyb + 1][j] = 0;
                    pohyb++;
                    test = 1;
                }


                pohyb--;

                if (i != 0 && grid[i - pohyb][j] == grid[i - 1 - pohyb][j] && grid[i - pohyb][j] != last_used) {
                    grid[i - pohyb - 1][j] *= 2;
                    last_used = grid[i - pohyb - 1][j];
                    grid[i - pohyb][j] = 0;
                    test = 1;
                }
            }
        }
    }
    return test;
}


int Right(int grid[4][4])
{
    
    int test = 0;
    for (int i = 3; i != -1; i--) {
        int last_used = 0;
        for (int j = 3; j != -1; j--) {
            if (grid[i][j] != 0) {
                int pohyb = 1;
                int moved_digit = grid[i][j];
                while (j != 3 && grid[i][j + pohyb] == 0 && j + pohyb != 4) {
                    grid[i][j + pohyb] = moved_digit;
                    grid[i][j + pohyb - 1] = 0;
                    pohyb++;
                    test = 1;
                }

                pohyb--;

                if (j != 3 && grid[i][j + pohyb] == grid[i][j + 1 + pohyb] && grid[i][j + pohyb] != last_used) {
                    grid[i][j + pohyb + 1] *= 2;
                    last_used = grid[i][j + pohyb + 1];
                    grid[i][j + pohyb] = 0;
                    test = 1;

                }
            }
        }
    }
    return test;
}
int Left(int grid[4][4])
{
    
    int test = 0;
    for (int i = 0; i != 4; i++) {
        int last_used = 0;
        for (int j = 0; j != 4; j++) {
            if (grid[i][j] != 0) {
                int pohyb = 1;
                int moved_digit = grid[i][j];


                while (j != 0 && grid[i][j - pohyb] == 0 && j - pohyb != -1) {
  
                    grid[i][j - pohyb] = moved_digit;
                    grid[i][j - pohyb + 1] = 0;
                    pohyb++;
                    test = 1;
                }

                pohyb--;

                if (j != 0 && grid[i][j - pohyb] == grid[i][j - 1 - pohyb] && grid[i][j - pohyb] != last_used) {
                    grid[i][j - pohyb - 1] *= 2;
                    last_used = grid[i][j - pohyb - 1];
                    grid[i][j - pohyb] = 0;
                    test = 1;
                }
            }
        }
    }
    return test;
}
int konec(int grid[4][4])
{// jestli je už konec, najde 2048
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (grid[i][j] == 2048)
            {
                printf("Vyhral jste!!! :)\n");
                return 0;
                
            }
        }
    }
    
    for (int i = 0; i != 4; i++) {
        for (int j = 0; j != 4; j++) {
            if (grid[i][j] != 0) {

                //L
                if (j != 0 && grid[i][j - 1] == 0 && j - 1 != -1) {//posun vlevo
                    return 1;
                }

                if (j != 0 && grid[i][j] == grid[i][j - 1]) {//soucet vlevo
                    return 1;

                }

                //U
                if (i != 0 && grid[i - 1][j] == 0 && i - 1 != -1) {
                    return 1;
                }
                if (i != 0 && grid[i][j] == grid[i - 1][j]) {
                    return 1;
                }

                //R
                if (j != 3 && grid[i][j + 1] == 0 && j + 1 != 4) {
                    return 1;
                }
                if (j != 3 && grid[i][j] == grid[i][j + 1]) {
                    return 1;
                }

                //D
                if (i != 3 && grid[i + 1][j] == 0 && i + 1 != 4) {
                    return 1;
                }
                if (i != 3 && grid[i][j] == grid[i + 1][j]) {
                    return 1;
                }

            }
        }
    }

    printf("Prohral jste!!! :(\n");
    return 0;
}

void vypis()
{
    system("cls");
    for (int a = 0; a < 4; a++)
    { // výpis gridu do konzole
        for (int b = 0; b < 4; b++)
        {
            printf("%4i ", grid[a][b]);
        }
        printf("\n\n");
    }
    printf("\n\n");
    printf("Skore: %i\n", score);
}

void hra() {
    int ch = 0;
    vypis();
    while ((ch = getch()) != 27) // loop hry do zmacknuti ESC
    {
        Action(ch); // switch s posuny podle vstupu (nahoru, dolu...)
        vypis(); // zápis gridu do konzole
        if (!(konec(grid))) {
            // skončí, když je někde buňka 2048
            printf("\nzmacknete x\n");
            while (getchar() != 'x');
            while (getchar() != '\n');
            break;
        }

    }

    fp = fopen("grid.txt", "w");
    zapis(fp, grid, &score);
    fclose(fp);
    

}

int main()
{
    int x=0;
    char  cmd, name[50];

    while (x == 0)
    {
        system("cls");		// smaze obrazovku
        printf("A: Nova hra\n");
        printf("B: Pokracovat\n");
        printf("C: Scoreboard\n");
        printf("Q: Konec\n\n");
     
        cmd = tolower(getchar());

        switch (cmd)
        {
        case 'a':
            score = 0;
            for (int i = 0; i != 4; i++) {
                for (int j = 0; j != 4; j++) {
                    grid[i][j] = 0;
                }
            }

            printf("Zadejte sve jmeno:  ");
            scanf("%s", &name);

            fp = fopen("grid.txt", "w");
            
            for (int i = 0; i != 2; i++) {
                printf("i: %d\n", i);
                rnd_gen(grid);
            }

            hra(); 
            break;
        case 'b':
            fp = fopen("grid.txt", "r");
            score = 0;
            nacti(fp, grid, &score);
            hra(); 
            break;
        case 'c':
            st = fopen("statistiky.txt", "r");
            
            stats(st);
            printf("zmacknete x\n");
            while (getchar() != 'x');
            while (getchar() != '\n');
            break;
        case 'q':
            x = 1;
            break;
        }
    }
    
}