#include "test_2048.h"
#include "stdio.h"
#include "stdlib.h" 
#include "string.h"
#include "time.h"
// už nevím která knihovna dělá co, ale myslím, že jsou všechny potřeba xd
#include "praceSeSoubory.h"
#include "conio.h" //getch()

#define UP 0x26
#define DOWN 0x28 // tohle je ukradené taky někde z internetu, nejsem si jistej, jestli to nakonec vůbec použijeme
#define LEFT 0x25 // má to být potom nějaká pomůcka ke čtení vstupů, ale nejsem si zatím jistý, jak to funguje
#define RIGHT 0x27
#define ESC 0x1B

int grid[4][4]; // dělalo mi to problémy, tak jsem to udělal globální, nic lepšího mě nenapadlo

void Pridej(int grid[4][4]);
void rnd_gen(int grid[4][4]);
void Down(int grid[4][4]);
void Up(int grid[4][4]);
void Left(int grid[4][4]);
void Right(int grid[4][4]);
void Action(int Arrow);

using namespace std;

void Pridej(int grid[4][4]) // +1 všemu, používal jsem ke zkoušení věcí
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            grid[y][x] += 1;
        }
    }
}

void rnd_gen(int grid[4][4]) // vytvoří nová čísla po posunutí
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
                break; // přemýšlím, jestli by sem nešel narvat game-over, 
                       //když se budeš snažit posunout, neotevře se žádné místo, tak by měla skončit hra, ale to nepočítá s tím, 
                       //že bys jen dal špatný směr a v jiném by to posunout šlo, idk
        }
    }
}

void Action(int Arrow)
{

    switch (Arrow)
    {
    case UP:
    {
        Up(grid);
        break;
    }
    case DOWN:
    {
        Down(grid);
        break;
    }
    case LEFT:
    {
        Left(grid);
        break;
    }
    case RIGHT:
    {
        Right(grid);
        break;
    }
    default:
    {
        // nic nedělat
        return;
    }
    }
    rnd_gen;
    //zapis(fp, grid);
}

void Down(int grid[4][4])
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
                grid[i + 1][j] += grid[i][j];
                grid[i][j] = 0;
                i++;
            }
            i--; // po posunutí nenulové buňky se posune o jedna nahoru a zkouší celý cyklus znovu
        }
    }
}
void Up(int grid[4][4])
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
                grid[i - 1][j] += grid[i][j];
                grid[i][j] = 0;
                i--;
            }
            i++;
        }
    }
}
void Right(int grid[4][4])
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
                grid[i][j + 1] += grid[i][j];
                grid[i][j] = 0;
                j++;
            }
            j--;
        }
    }
}
void Left(int grid[4][4])
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
                grid[i][j - 1] += grid[i][j];
                grid[i][j] = 0;
                j--;
            }
            j++;
        }
    }
}

int main()
{
    FILE* fp;
    fp = fopen("grid.csv", "r"); // otevření souboru s argumentem r -> ke čtení
    // buď ta tabulka musí být v out/build/x64_Debug (výchozí)/test_2048, nebo tam musí být přesná cesta na soubor 
    // (C:/Users/Lukáš/source/repos/test_2048/gridd.csv), ale s lomítky dopředu
    // tak ne, teď to muselo být v jiné debug složce... tak jsem to hodil do všech 3 a dlabal na to

    //vytvor_grid(fp);
    //fp = fopen("grid.csv", "r"); -> tyhle dva řádky by se musely dát na začátek nové hry místo "nacti"

    nacti(fp, grid);

    for (int a = 0; a < 4; a++)
    { // výpis gridu do konzole
        for (int b = 0; b < 4; b++)
        {
            printf("%i ", grid[a][b]);
        }
        printf("\n");
    }



    printf("\n\n");









    int Arrow;
    scanf("%i", &Arrow);
        Action(Arrow);

   
    /*
        char kam;
        kam = getchar();
        //voe nevím, musíš tam dávat enter, ale funguje to víceméně
        if (kam == 's' || kam == 'S') {
            Down(grid);
            
        }
        else if (kam == 'W' || kam == 'w') {
            Up(grid);

        }
        else if (kam == 'D' || kam == 'd') {
            Right(grid);

        }
        else if (kam == 'A' || kam == 'a') {
            Left(grid);

        }
    */




    for (int a = 0; a < 4; a++)
    { // výpis gridu do konzole
        for (int b = 0; b < 4; b++)
        {
            printf("%i ", grid[a][b]);
        }
        printf("\n");
    }

    fp = fopen("grid.csv", "w"); // otevření s argumentem w pro psaní, vymaže soubor a nechá nás psát
    // zkoušel jsem to i s r+ (otevře ke čtení i psaní), ale to nám nefunguje, protože to potom nevymaže soubor a když chceš přepsat nějaké buňky, je to hloupé
    zapis(fp, grid);
    fclose(fp); // soubor je otevřený, musí se zavřít, jinak se dojebe
}