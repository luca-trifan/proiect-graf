#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>

#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define BLU "\e[0;34m"
#define YEL "\e[0;33m"
#define MAG "\u001b[35m"
#define CYN "\u001b[36m"
#define REDB "\e[41m"


using namespace std;

ifstream fin("harta.in");

int n, m, hartaCost[100][100], hartaDist[100][100];

struct statie
{
    int x,y;
};

struct linie
{
    int nr;
    statie traseu[100];
};

void citire()
{
    fin>>n;
    int x,y,cost,dist;
    while(fin>>x>>y>>cost)
    {
        hartaCost[x][y]=cost;
        hartaDist[x][y]=dist;
    }
}

void costMin(int a[100][100])
{
    for(int k = 1 ; k <= n ; k ++)
        for(int i = 1 ; i <= n ; i ++)
            for(int j = 1 ; j <= n ; j ++)
                if(a[i][j] > a[i][k] + a[k][j])
                    a[i][j] = a[i][k] + a[k][j];
}

void royWarshall(int a[100][100])
{
    for(int kk = 1; kk <= n; kk++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                if(i != j && a[i][j] == 0)
                    a[i][j] = a[i][kk] * a[kk][j];
}

void dispatcher()
{
    int opt;
    do
    {
        system("CLS");
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

int main()
{
    system("Color 0F");
    citire();
    dispatcher();
    return 0;
}
