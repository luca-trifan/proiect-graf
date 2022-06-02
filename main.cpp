#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <io.h>
#include <cmath>
#include <fcntl.h>

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

int n, m, hartaCost[100][100], hartaDist[100][100], nrLinii, hartaCoord[100][100], floydCost[100][100], floydDist[100][100], traseuCost[100], traseuDist[100];

int dest, nodStart, xStart, yStart;

char hartaSimbol[250][250]= {NULL};

struct linie
{
    int nr, nrStatii;
    int traseu[100];
} listLinii[100];

struct nod
{
    int x,y;
};

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

nod gasestePunct(int x)
{
    nod punct;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(hartaCoord[i][j]==x)
            {
                punct.x=i+1;
                punct.y=j+1;
            }
    return punct;
}

void construiesteHartaSimbol()
{
    int cont=0, rad=sqrt(n);
    for(int i=1; i<=n; i+=2)
        for(int j=1; j<=n; j+=2)
        {
            cont++;
            hartaSimbol[i][j]=static_cast<char>(cont);
        }
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
        {
            if(hartaDist[i][j]!=0 && hartaDist[j][i]!=0 && i<j)
            {
                nod puncti=gasestePunct(i);
                nod punctj=gasestePunct(j);
                if(puncti.x%2==0)
                    puncti.x+=1;
                if(puncti.y%2==0)
                    puncti.y+=1;
                if(punctj.x%2==0)
                    punctj.x+=1;
                if(punctj.y%2==0)
                    punctj.y+=1;
                if(puncti.x==punctj.x)
                    hartaSimbol[puncti.x][puncti.y+1]='\u2194';
                if(puncti.y==punctj.y)
                    hartaSimbol[puncti.x+1][puncti.y]='\u2195';
            }
            if(hartaDist[i][j]!=0 && hartaDist[j][i]==0)
            {
                nod puncti=gasestePunct(i);
                nod punctj=gasestePunct(j);
                if(puncti.x%2==0)
                    puncti.x+=1;
                if(puncti.y%2==0)
                    puncti.y+=1;
                if(punctj.x%2==0)
                    punctj.x+=1;
                if(punctj.y%2==0)
                    punctj.y+=1;
                if(puncti.x==punctj.x)
                {
                    if(puncti.y<punctj.y)
                        hartaSimbol[puncti.x][puncti.y+1]='\u2192';
                    else
                        hartaSimbol[puncti.x][puncti.y+1]='\u2190';
                }
                if(puncti.y==punctj.y)
                {
                    if(puncti.x<punctj.x)
                        hartaSimbol[puncti.x+1][puncti.y]='\u2193';
                    else
                        hartaSimbol[puncti.x+1][puncti.y]='\u2191';
                }
            }
        }
}

void displayMap()
{
    construiesteHartaSimbol();
    for(int i=1; i<n*2; i++)
    {
        for(int j=1; j<n*2; j++)
            wcout<<hartaSimbol[i][j]<<' ';
        wcout<<endl;
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

void reconstituieDrum(int i, int j, int a[100][100], int b[100], int &lTraseu)
{
    int ok=0;
    for(int k=1; k<=n && !ok; k++)
    {
        if(i!=k && j!=k)
            if(a[i][j]==a[i][k]+a[k][j])
            {
                reconstituieDrum(i, k, a, b, lTraseu);
                reconstituieDrum(k, j, a, b, lTraseu);
                ok=1;
            }
    }
    if(!ok)
        b[++lTraseu]=j;
}

void royFloyd(int a[100][100])
{
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            if(a[i][j]==0 && i!=j)
                a[i][j]=INF;
    for(int k = 1 ; k <= n ; k ++)
        for(int i = 1 ; i <= n ; i ++)
            for(int j = 1 ; j <= n ; j ++)
                if(i!=k && j!=k && i!=j)
                    if(a[i][j] > a[i][k] + a[k][j])
                        a[i][j] = a[i][k] + a[k][j];
    /*for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            if(a[i][j]==INF)
                a[i][j]=0;*/
}


int cautaLinie(int x, int y)
{
    for(int i=1; i<=nrLinii; i++)
        for(int j=1; j<listLinii[i].nrStatii; j++)
            if(listLinii[i].traseu[j]==x && listLinii[i].traseu[j+1]==y)
                return listLinii[i].nr;
    return 0;
}

void inputTraseu()
{
    double x,y;
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
}

void celMaiIeftin()
{
    int leng=0;
    reconstituieDrum(nodStart, dest, floydCost, traseuCost, leng);
    cout<<leng<<endl;
    int i=1;
    cout<<"Traseu propus: ";
    while(i<leng)
    {
        cout<<"Linia "<<cautaLinie(i, i+1);
        cout<<traseuCost[i]<<' ';
        while(cautaLinie(i, i+1))
        {
            i++;
            cout<<traseuCost[i]<<' ';
        }
        i++;
    }
}

void celMaiScurt()
{
    int leng=0;
    reconstituieDrum(nodStart, dest, floydDist, traseuDist, leng);
    int i=1;
    cout<<"Traseu propus: ";
    while(i<leng)
    {
        cout<<"Linia "<<cautaLinie(i, i+1);
        cout<<traseuDist[i]<<' ';
        while(cautaLinie(i, i+1))
        {
            i++;
            cout<<traseuDist[i]<<' ';
        }
        i++;
    }
}


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
        cout<<endl;
        cout<<YEL "1: Afisare harta"<<endl;
        cout<<RED "2: Modificare traseu"<<endl;
        cout<<BLU "3: Cel mai scurt drum"<<endl;
        cout<<GRN "4: Cel mai ieftin drum"<<endl;
        cout<<CYN "0: Iesire"<<endl;
        cout<<NC "Va rog selectati comanda: ";
        cin>>opt;
        if(opt != 0)
        {
            switch(opt)
            {
            case 1:
                displayMap();
            case 2:
                inputTraseu();
            case 3:
                celMaiScurt();
            case 4:
                celMaiIeftin();
            }
            getch();
        }
    }
    while(opt!=0);
}

int main()
{
    system("Color 0F");
    system("echo off");
    system("chcp 65001");
    system("CLS");
    citire();
    inputTraseu();
    system("CLS");
    dispatcher();
    return 0;
}
