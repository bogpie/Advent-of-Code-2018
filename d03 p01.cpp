#include <fstream>
#include <cstring>
#define type unsigned long long

using namespace std;

ifstream fin ("3a.in");
ofstream fout("3a.out");

const type I=10000,NCAR=1000;
type imin=I,jmin=I,i,j,imax,stanga,dreapta;
type sus,jos,jmax,ncom,id,lg,icar,lungime,inaltime;
type tab[I][I];
char str[NCAR];



void minimax()
{
    if (sus<=imin) imin=sus;
    if (stanga<=jmin) jmin=stanga;
    if (jos>=imax) imax=jos;
    if (dreapta>=jmax) jmax=dreapta;

}

void makenr(type &nr,type &icar)
{
    type cif=str[icar]-'0';
    while (icar<lg && cif>=0 && cif<=9)
    {
        nr=nr*10+cif;
        ++icar;
        cif=str[icar]-'0';

    }
}

void makeallnr()
{
    fin >> str;

    fin >> str;
    icar=0;
    lg=strlen(str);
    stanga=dreapta=sus=jos=inaltime=lungime=0;
    makenr(stanga,icar);
    ++icar; ++stanga;
    makenr(sus,icar);
    ++icar; ++sus;

    fin >> str;
    icar=0;
    lg=strlen(str);
    makenr(lungime,icar);
    ++icar;
    makenr(inaltime,icar);
    ++icar;

    jos=sus+inaltime-1;
    dreapta=stanga+lungime-1;

    minimax();

}


int main()
{
    while (fin>>str)
    {
        makeallnr();

        for (i=sus; i<=jos; ++i)
        {
            for (j=stanga; j<=dreapta; ++j)
            {
                ++tab[i][j];
            }
        }
    }

    for (i=imin; i<=imax; ++i)
    {
        for (j=jmin; j<=jmax; ++j)
        {
            if (tab[i][j]>1)
            {
                ++ncom;
            }
        }
    }

    fout << ncom;

    return 0;
}
