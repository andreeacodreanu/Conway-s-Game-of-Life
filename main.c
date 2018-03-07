//Conway`s Game of Life
#include <stdio.h>
#include <stdlib.h>
#define MAX 500
#define For(x, y) for (i = 1; i <= x; i++) for (j = 1; j <= m; j++)

int v[MAX][MAX], n, m;

/*Subprogramul vecini numara vecinii fiecarei celule astfel:
    In cazul planar(P):
    -daca celula se afla pe colt se aduna valorile celor 3 celule vecine
    -daca celula se afla pe margine(fara colt) se aduna valorile celor 5
     celule vecine
    -altfel se va face suma valorilor tuturor celor 8 celule vecine
    In cazul toroidal(T):
    -se vor face sumele la fel ca in cazul reprezentarii planare si se vor
    adauga restul vecinilor (5 in cazul celulelor de pe colturi si 3 in cazul
    celulelor de pe margine)
  Subprogramul primeste ca parametrii indicii i si j si modul de reprezentare
  'P'-planar sau 'T'-toroidal si returneaza prin variabila vec numarul
  vecinilor.
*/
int vecini(int i, int j, char c)
{
    int vec = 0;
    if (i == 1 && j == 1)
    {
        vec = v[i][j+1] + v[i+1][j] + v[i+1][j+1];
        if (c == 'T') vec = vec + v[i][m] + v[i+1][m] + v[n][j] + v[n][j+1] + v[n][m];
    }
    if (i == 1 && j != 1 && j != m)
    {
        vec = v[i][j+1] + v[i+1][j] + v[i+1][j+1] + v[i][j-1] + v[i+1][j-1];
        if (c == 'T')
            vec = vec + v[n][j-1] + v[n][j] + v[n][j+1];
    }
    else if (i == 1 && j == m)
    {
        vec = v[i][j-1] + v[i+1][j-1] + v[i+1][j];
        if (c == 'T')
            vec = vec + v[n][1] + v[1][1] + v[2][1] + v[n][m-1] + v[n][m];
    }
    else if (i == n && j == 1)
    {
        vec = v[n-1][j] + v[i-1][j+1] + v[i][j+1];
        if (c == 'T')
            vec = vec + v[1][m] + v[1][1] + v[1][2] + v[n][m] + v[n-1][m];
    }
    else if (i == n && j != 1 && j != m)
    {
        vec = v[i][j-1] + v[i][j+1] + v[i-1][j-1] + v[i-1][j] + v[i-1][j+1];
        if (c == 'T')
            vec = vec + v[1][j-1] + v[1][j] + v[1][j+1];
    }
    else if (i == n && j == m)
    {
        vec = v[n][m-1] + v[n-1][m-1] + v[n-1][m];
        if (c == 'T')
            vec = vec + v[1][1] + v[n][1] + v[n-1][1] + v[1][m] + v[1][m-1];
    }
    else if (j == 1 && i != 1 && i != n)
    {
        vec = v[i-1][j] + v[i-1][j+1] + v[i][j+1] + v[i+1][j+1] + v[i+1][j];
        if (c == 'T')  vec
            = vec + v[i-1][m] + v[i][m] + v[i+1][m];
    }
    else if (j == m && i != 1 && i != n)
    {
        vec = v[i-1][j] + v[i-1][j-1] + v[i][j-1] + v[i+1][j-1] + v[i+1][j];
        if (c == 'T')
            vec = vec + v[i-1][1] + v[i][1] + v[i+1][1];
    }
    else vec = v[i+1][j-1] + v[i][j-1] + v[i-1][j-1] + v[i-1][j]
                 + v[i+1][j] + v[i-1][j+1] + v[i][j+1] + v[i+1][j+1];
    return vec;
}
/*Subprogramul populare returneaza prin variabila nr numarul valorilor 1 din
  matrice.
*/
int populare()
{
    int i, j, nr = 0;
    For(n,m)
    nr = nr + v[i][j];
    return nr;
}

int main()
{
    char c;
    int i, j, a[MAX][MAX], k;
    printf("Introduceti tipul de reprezentare (T sau P): ");
    scanf("%c", &c);

    if ((c != 'T') && (c != 'P'))
    {
        printf("Optiune invalida");
        exit(0);
    }

    printf("Introduceti dimensiunile matricei \n m = ");
    scanf("%d", &m);
    printf(" n = ");
    scanf("%d", &n);
    printf(" k = ");
    scanf("%d", &k);

    printf("Introduceti matricea \n");
    For(n, m)
    {
        scanf("%d", &v[i][j]);  //citirea matricei
        a[i][j] = v[i][j];         //se creeaza o matrice a, copie a lui v
    }

    int maxim = populare();
    while (k)
    {
        For(n, m)
        {
            int x = vecini(i, j, c);  //x retine numarul vecinilor celulei
            //se retine in a evolutia celulelor conform cerintei
            if (v[i][j] == 1 && x < 2)  a[i][j] = 0;
            if (v[i][j] == 1 && x > 3)  a[i][j] = 0;
            if (v[i][j] == 0 && x == 3)  a[i][j] = 1;
        }
        For(n, m)
        {
            //se transmit matricii v schimbarile din etapa curenta
            if (a[i][j] == 1) v[i][j] = 1;
            if (a[i][j] == 0)  v[i][j] = 0;
        }
        int x = populare();
        if (x > maxim)  maxim = x; //se calculeaza numarul maxim de valori de 1
        k--;
    }

    printf("\n");
    //afisarea matricei rezultate dupa cele k etape de transformare
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= m; j++)
            printf("%d ",v[i][j]);
        printf("\n");
    }

    //afisarea gradului maxim de populare
    printf("\nGradul maxim de populare: ");
    float p = (float)(maxim*100)/(n*m);
    printf("%.*f%%", 3, p);
    return 0;
}
