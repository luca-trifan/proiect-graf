#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <cmath>

#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define BLU "\e[0;34m"
#define YEL "\e[0;33m"
#define MAG "\u001b[35m"
#define CYN "\u001b[36m"
#define REDB "\e[41m"
#define INF 99999



using namespace std;

int n, m, hartaCost[100][100], hartaDist[100][100], nrLinii, hartaCoord[100][100], floydCost[100][100], floydDist[100][100];

struct linie
{
    int nr, nrStatii;
    int traseu[100];
} listLinii[100];

void citire()
{
    ifstream fin("harta.in");
    fin>>n;
    int x,y,cost,dist, cont=0;
    while(fin>>x>>y>>cost>>dist)
    {
        hartaCost[x][y]=cost;
        hartaDist[x][y]=dist;
    }
    for(int i=0; i*i<n; i++)
        for(int j=0; j*j<n; j++)
        {
            cont++;
            hartaCoord[i][j]=cont;
        }
    ifstream fin2("linii.in");
    fin2>>nrLinii;
    for(int i=1; i<=nrLinii; i++)
    {
        fin2>>listLinii[i].nr>>listLinii[i].nrStatii;
        for(int j=1; j<=listLinii[i].nrStatii; j++)
            fin2>>listLinii[i].traseu[j];
    }
}

void afisare(int a[100][100], int nr)
{
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<n; j++)
            cout<<a[i][j]<<' ';
        cout<<endl;
    }
    cout<<endl;
}

void copiaza(int a[100][100], int b[100][100], int nr)
{
    for(int i=1; i<=nr; i++)
        for(int j=1; j<=nr; j++)
            b[i][j]=a[i][j];
}

void reconstituieDrum(int i, int j,int a[100][100])
{
    int g=0,k=1;
    while(!g&&k<=n)
    {
        if(i!=k&&j!=k)
            if(a[i][j]=a[i][k]+a[k][j])
        {
            reconstituieDrum(i,k,a);
            reconstituieDrum(k,j,a);
            g=1;
        }
        k++;
    }
    if(!g)
        cout<<j<<' ';
}

void royFloyd(int a[100][100])
{
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            if(a[i][j]==0)
                a[i][j]=INF;
    for(int k = 1 ; k <= n ; k ++)
        for(int i = 1 ; i <= n ; i ++)
            for(int j = 1 ; j <= n ; j ++)
                if(a[i][j] > a[i][k] + a[k][j])
                    a[i][j] = a[i][k] + a[k][j];
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            if(a[i][j]==INF)
                a[i][j]=0;
}

void royWarshall(int a[100][100])
{
    for(int kk = 1; kk <= n; kk++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                if(i != j && a[i][j] == 0)
                    a[i][j] = a[i][kk] * a[kk][j];
}

void inputTraseu()
{
    double x,y;
    int dest, nodStart, xStart, yStart;
    cout<<"Introduceti coordonatele dvs"<<endl;
    cin>>x>>y;
    cout<<"Introduceti numarul nodului de destinatie"<<endl;
    cin>>dest;
    xStart = round(x);
    yStart = round(y);
    cout<<xStart<<' '<<yStart<<endl;
    nodStart = hartaCoord[xStart][yStart];
    cout<<nodStart<<endl;
    copiaza(hartaCost, floydCost, n);
    copiaza(hartaDist, floydDist, n);
    royFloyd(floydCost);
    royFloyd(floydDist);
    reconstituieDrum(nodStart, dest, floydCost);
    //afisare(floydCost, n);
    //afisare(floydDist, n);
}

/*
void dispatcher()
{
    int opt;
    do
    {
        system("CLS");
        cout << R"(
    ___            _      _         ___     _                _
   | _ \  __ _    | |_   | |_      | __|   (_)    _ _     __| |    ___      _ _
   |  _/ / _` |   |  _|  | ' \     | _|    | |   | ' \   / _` |   / -_)    | '_|
  _|_|_  \__,_|   _\__|  |_||_|   _|_|_   _|_|_  |_||_|  \__,_|   \___|   _|_|_
_| """ |_|"""""|_|"""""|_|"""""|_| """ |_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|
"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'
    )";
        cout<<MAG "1: Cel mai aventuros drum"<<endl;
        cout<<CYN "2: Cel mai lung drum"<<endl;
        cout<<MAG "3: Cel mai scurt drum"<<endl;
        cout<<CYN "4: Cea mai multa energie ramasa"<<endl;
        cout<<MAG "5: Cea mai putina energie ramasa"<<endl;
        cout<<CYN "6: Cel mai eficient drum (in cel mai scurt timp)"<<endl;
        cout<<MAG "7: Cel mai putin eficient drum (in cel mai lung timp)"<<endl;
        cout<<CYN "10: Afisare matrice"<<endl;
        cout<<MAG "0: Iesire"<<endl;
        cout<<NC "Va rog selectati comanda: ";
        cin>>opt;
        if(opt != 0)
        {
            if(opt==10)
            {
                for(int i=1; i<=n; ++i)
                {
                    for(int j=1; j<=m; ++j)
                        cout<<a[i][j]<<' ';
                    cout<<endl;
                }
                cout<<endl;
                for(int i=1; i<=n; ++i)
                {
                    for(int j=1; j<=m; ++j)
                        cout<<sub[i][j]<<' ';
                    cout<<endl;
                }
                cout<<endl;
            }
            else
            {
                mod=opt;
                t[i0][j0]=1;
                traseu(a,t,i0,j0,2);
                afisSol();
            }
            getch();
        }

    }
    while(opt!=0);
}
*/
int main()
{
    system("Color 0F");
    citire();
    afisare(hartaCost, n);
    afisare(hartaDist, n);
    inputTraseu();
    //dispatcher();
    return 0;
}
