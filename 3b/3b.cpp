#include <fstream>
#include <cstring>
#define type unsigned long long

using namespace std;

ifstream fin ("3b.in");
ofstream fout("3b.out");

const type I=10000,NCAR=1000;
type i,j,imax,stanga,dreapta;
type sus,jos,jmax,ncom,nelf,ielf,lg,icar,lungime,inaltime;
type tabclaim[I][I];
bool no;
char str[NCAR];


struct sct
{
    type stanga,dreapta,sus,jos;
}velf[I];

void minimax()
{
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
    ++icar;
    ++stanga;
    makenr(sus,icar);
    ++icar;
    ++sus;

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

    velf[++nelf].stanga=stanga;
    velf[nelf].dreapta=dreapta;
    velf[nelf].sus=sus;
    velf[nelf].jos=jos;
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
                ++tabclaim[i][j];
            }
        }
    }


    /*for (i=0; i<=imax; ++i)
    {
        for (j=0; j<=jmax; ++j)
        {
            fout << tabclaim[i][j] << ' ';
        }
        fout << "\n";
    }*/



    for (ielf=1; ielf<=nelf; ++ielf)
    {
        no=0;
        sus=velf[ielf].sus;
        jos=velf[ielf].jos;
        stanga=velf[ielf].stanga;
        dreapta=velf[ielf].dreapta;
        for (i=sus; i<=jos; ++i)
        {
            for (j=stanga; j<=dreapta; ++j)
            {
                if (tabclaim[i][j]!=1)
                {
                    i=jos;
                    no=1;
                    break;
                }
            }
        }
        if (!no)
        {
            fout << ielf ;
            return 0;
        }
    }



    return 0;
}
