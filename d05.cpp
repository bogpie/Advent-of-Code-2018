#include <fstream>
#include <stack>
#include <cmath>
#include <cstring>

using namespace std;

ifstream fin ("5.in");
ofstream fout("5.out");

char car,tp;
//short int query;
char sir[50002],stiva[50002];
int ind[130],vfr[30],lg,ilit,mxfr,mnpol=50002,u,ielim,lgfin;

void asoc()
{
    char small='a',big='A';
    for (int ilit=1; ilit<=26; ++ilit)
    {
        ind[small++]=ind[big++]=ilit;
    }
}


bool isopp (char car1,char car2)
{
    if (abs(car1-car2) == 32) return 1;
    return 0;
}


void destroy(int ielim,int &u)
{
    int icar=0;
    int lg=strlen(sir);

    while (icar<lg && ind[sir[icar]]==ielim)
    {
        ++icar;
    }

    stiva[++u]=sir[icar++];

    while (icar<lg)
    {
        char car=sir[icar],tp;

        if (ind[car]==ielim)
        {
            ++icar;
            continue;
        }

        if(u!=-1)
        {
            tp=stiva[u];
        }
        ///???
        if ( isopp ( tp, car ))  // && !stiva.empty() )
        {
            --u;
        }
        else
        {
            stiva[++u]=car;
        }
        ++icar;
    }


}


int main()
{
    //fin >> query;
    /*query=1;
    if (query==1)
    {
        sol1();
        return 0;
    }*/

    asoc();
    fin >>sir;
    u=-1;
    destroy(0,u); lgfin=u+1;
    fout << lgfin << '\n' ;
   // strcpy(sir,stiva);

    for (ilit=1;ilit<=26;++ilit)
    {
        ielim=ilit;
        u=-1;
        destroy(ielim,u);
        lgfin=u+1;
        if (lgfin<mnpol)
        {
            mnpol=lgfin;
        }
    }

    fout << mnpol;



    return 0;
}
