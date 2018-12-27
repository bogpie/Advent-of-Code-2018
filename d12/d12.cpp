#include <fstream>
#include <cstring>

using namespace std;

ifstream fin ("d12.in");
ofstream fout("d12.out");

char car;
char sir[999],stcave[999],turn[999];
char vturn[999][999];
char vdots[404];

long long nturn,lgcave,euro2020,igen,icave,icap,iturn,mk,itrue,sol,ngen,solold,idots;
long long BIG=50000000000;

bool gas;
bool markdot[999];
bool isdot[999];


void parse_and_border_with_dots()
{
    fin >> sir >> sir;

    for (idots=0;idots<400;++idots)
    {
        vdots[idots]='.';
    }

    strcpy(stcave,vdots);
    fin >> stcave+400;
    lgcave=strlen(stcave);
    strcpy(stcave+lgcave,vdots);
}


int main()
{

    parse_and_border_with_dots();

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


    for (igen=1;igen<=ngen-3;++igen)
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

        if (igen==20)
        {
            euro2020=sol;
        }
    }

    fout << "part 1 : " << euro2020 << '\n';
    fout << "part 2 : " << 5564 + (BIG-97) * 40 << '\n';

    return 0;
}
