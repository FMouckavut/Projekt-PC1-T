#include "test_2048.h"
#include "stdio.h"
#include "stdlib.h" 
#include "string.h"
#include "time.h"
// už nevím která knihovna dělá co, ale myslím, že jsou všechny potřeba xd
#include "praceSeSoubory.h"
#include "conio.h" //getch()

int grid[5][4]; // dělalo mi to problémy, tak jsem to udělal globální, nic lepšího mě nenapadlo

void rnd_gen(int grid[5][4]);
void Down(int grid[5][4]);
void Up(int grid[5][4]);
void Left(int grid[5][4]);
void Right(int grid[5][4]);
void Action(int ch);

int score = 0;
FILE* fp;

using namespace std;

void rnd_gen(int grid[5][4]) // vytvoří nová čísla po posunutí
{
    int pridej, g, h;
    srand(time(NULL)); // inicializace toho rand, myslím, že tam musí být, idk
    g = rand() % 4; // náhodný číslo od 0-3
    h = rand() % 4;

    if ((g + h) % 2 == 0) // pseudo náhodný výběr buď 2/4
        pridej = 2;
    else
        pridej = 4;

    for (int y = 0; y < 20; y++) // tohle není dokonalý, mohlo by se to netrefit a neudělat nic nového, i kdyby bylo ještě místo
    {
        if (grid[g][h] == 0)
        {
            grid[g][h] = pridej;
            return;
        }
        else
        {
            if (y == 19)
            {
                for (int i = 0; i < 4; i++)
                { // zkusí po 20 pokusech celou matici, jestli tam fakt není 0
                    for (int j = 0; j < 4; j++)
                    {
                        if (grid[i][j] == 0)
                            grid[i][j] = pridej;
                    }
                }
            }
            else
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
            break;
        case 80:
            Down(grid);
            break;
        case 77:
            Right(grid);
            break;
        case 75:
            Left(grid);
            break;
        }
    }
    rnd_gen(grid);
    fp = fopen("grid.txt", "w");
    zapis(fp, grid, &score);
}

void Down(int grid[5][4])
{
    int i, j;
    for (j = 0;j < 4;j++)
    {
        i = 2; // dolů, takže to začne z políčka jedno od spodního kraje
        while (1)
        {
            while (grid[i][j] == 0)
            { // zkouší od spodu každou buňku, jestli je 0, pokud není, jde dál
                if (i == -1)
                    break;//pokud jsou všechny 0, končí
                i--;
            }
            if (i == -1) // došel mimo grid, končí
                break;
            while (i < 3 && (grid[i + 1][j] == 0 || grid[i][j] == grid[i + 1][j]))
            {// jde z místa kde našel číslo dolů a pokud je buňka pod číslem buď 0, nebo stejná, sečtě je (posune číslo dolů),
             // vymaže původní buňku, přidá 1 k i, takže se zase posune o 1 dolů a opakuje
                if (grid[i][j] == grid[i + 1][j])
                {// pokud se 2 buňky sečtou, jejich součet se přidá ke skóre
                    score += 2*grid[i + 1][j];
                }
                grid[i + 1][j] += grid[i][j];
                grid[i][j] = 0;
                i++;
            }
            i--; // po posunutí nenulové buňky se posune o jedna nahoru a zkouší celý cyklus znovu
        }
    }
}
void Up(int grid[5][4])
{
    int i, j;
    for (j = 0;j < 4;j++)
    {
        i = 1;
        while (1)
        {
            while (grid[i][j] == 0)
            {
                if (i == 4)
                    break;
                i++;
            }
            if (i == 4)
                break;
            while (i > 0 && (grid[i - 1][j] == 0 || grid[i][j] == grid[i - 1][j]))
            {
                if (grid[i][j] == grid[i - 1][j])
                {
                    score += 2*grid[i - 1][j];
                }
                grid[i - 1][j] += grid[i][j];
                grid[i][j] = 0;
                i--;
                
            }
            i++;
        }
    }
}
void Right(int grid[5][4])
{
    int i, j;
    for (i = 0;i < 4;i++)
    {
        j = 2;
        while (1)
        {
            while (grid[i][j] == 0)
            {
                if (j == -1)
                    break;
                j--;
            }
            if (j == -1)
                break;
            while (j < 3 && (grid[i][j + 1] == 0 || grid[i][j] == grid[i][j + 1]))
            {
                if (grid[i][j] == grid[i][j + 1])
                {
                    score += 2*grid[i][j + 1];
                }
                grid[i][j + 1] += grid[i][j];
                grid[i][j] = 0;
                j++;
            }
            j--;
        }
    }
}
void Left(int grid[5][4])
{
    int i, j;
    for (i = 0;i < 4;i++)
    {
        j = 1;
        while (1)
        {
            while (grid[i][j] == 0)
            {
                if (j == 4)
                    break;
                j++;
            }
            if (j == 4)
                break;
            while (j > 0 && (grid[i][j - 1] == 0 || grid[i][j] == grid[i][j - 1]))
            {
                if (grid[i][j] == grid[i][j - 1])
                {
                    score += 2*grid[i][j - 1];
                }
                grid[i][j - 1] += grid[i][j];
                grid[i][j] = 0;
                j--;
            }
            j++;
        }
    }
}
int konec(int grid[5][4])
{// jestli je už konec, najde 2048
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            if (grid[i][j] == 2048) 
            {
                printf("ende. vyhra");
                return 1;
            }
        }
    }
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

int main()
{
    fp = fopen("grid.txt", "r"); // otevření souboru s argumentem r -> ke čtení
    vytvor_grid(fp); // vytvoří celý nový soubor, takže nemusí existovat při zapínání poprvé
                     // musí tam být, pokud zvolí novou hru, jinak funkce nacti
     
    // buď ta tabulka musí být v out/build/x64_Debug (výchozí)/test_2048, nebo tam musí být přesná cesta na soubor 
    // (C:/Users/Lukáš/source/repos/test_2048/gridd.csv), ale s lomítky dopředu
    // tak ne, teď to muselo být v jiné debug složce... tak jsem to hodil do všech 3 a dlabal na to

    nacti(fp, grid, &score);

    int ch = 0;
    vypis();
    while ((ch = getch()) != 27) // loop hry do zmacknuti ESC
    {
        Action(ch); // switch s posuny podle vstupu (nahoru, dolu...)
        vypis(); // zápis gridu do konzole
        if (konec(grid) == 1) // skončí, když je někde buňka 2048
            break;
    }
}