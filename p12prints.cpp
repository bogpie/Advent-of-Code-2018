#include <fstream>
#include <cstring>

using namespace std;

ifstream fin ("p12.in");
ofstream fout("p12.out");

char car;
char sir[999],stcave[999],turn[999];
char vturn[999][999];

long long nturn,lgcave,igen,icave,icap,iturn,mk,itrue,sol,ngen,solold;

bool gas;
bool markdot[999];
bool isdot[999];

int main()
{
    /// bordare manuala input !!
    fin >> sir >> sir;
    fin >> stcave;

    nturn=1;
    while (fin>>vturn[nturn])
    {
        fin >> sir >> car;
        if (car=='#')
        {
            isdot[nturn]=0;
        }
        else
        {
            isdot[nturn]=1;
        }
        ++nturn;
    }
    lgcave=strlen(stcave);

    ngen=400;

    for (igen=1;igen<=ngen;++igen)
    {
        for (icave=0;icave<lgcave;++icave)
        {
            markdot[icave]=1;
        }
        for (icap=0;icap<lgcave-5;++icap)
        {
            strcpy(turn,stcave+icap);
            turn[5]='\0';
            gas=0;
            for (iturn=1;iturn<=nturn;++iturn)
            {
                if (!strcmp(turn,vturn[iturn]))
                {
                    gas=1;
                    markdot[icap+2]=isdot[iturn];
                    break;
                }
            }
            if (!gas) markdot[icap+2]=1;
        }



        for (icave=0;icave<lgcave;++icave)
        {

            mk=markdot[icave];
            if (mk==1)
            {
                stcave[icave]='.';
            }
            else
            {
                stcave[icave]='#';
            }
        }
        if (igen==15)
        {
            long long aux=1;
        }

        solold=sol;
        sol=0;
        for (icave=0;icave<lgcave;++icave)
        {
            itrue=icave-400;
            if (stcave[icave]=='#')
            {
                sol+=itrue;
            }
        }
        fout << sol<< ' ' << sol-solold << '\n';


    }



    return 0;
}
