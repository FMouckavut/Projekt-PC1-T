#include "test_2048.h"
#include "stdio.h"
#include "stdlib.h" 
#include "string.h"
#include "time.h"
// už nevím která knihovna dělá co, ale myslím, že jsou všechny potřeba xd
#include "praceSeSoubory.h"

void Pridej(int grid[4][4]);
void rnd_gen(int grid[4][4]);

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

int main()
{
    FILE* fp = fopen("grid.csv", "r");; // otevření souboru s argumentem r -> ke čtení
    // buď ta tabulka musí být v out/build/x64_Debug (výchozí)/test_2048, nebo tam musí být přesná cesta na soubor 
    // (C:/Users/Lukáš/source/repos/test_2048/gridd.csv), ale s lomítky dopředu
    int grid[4][4];

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

    rnd_gen(grid); 
    printf("\n\n");

    for (int a = 0; a < 4; a++)
    { // výpis gridu do konzole
        for (int b = 0; b < 4; b++)
        {
            printf("%i ", grid[a][b]);
        }
        printf("\n");
    }

    fp = freopen("grid.csv", "w", fp); // otevření s argumentem w pro psaní, vymaže soubor a nechá nás psát
    // zkoušel jsem to i s r+ (otevře ke čtení i psaní), ale to nám nefunguje, protože to potom nevymaže soubor a když chceš přepsat nějaké buňky, je to hloupé
    zapis(fp, grid);
    fclose(fp); // soubor je otevřený, musí se zavřít, jinak se dojebe
}