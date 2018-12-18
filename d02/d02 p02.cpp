#include <fstream>
#include <cstring>
#define typ unsigned long long

using namespace std;

ifstream fin ("2b.in");
ofstream fout("2b.out");


const typ NIDMAX=1111,LGMAX=1111;
typ nid,iid,jid,lgi,lg,i,j,lgj,idel;
typ lev[LGMAX][LGMAX];
char tab[NIDMAX][LGMAX],aux[LGMAX];

void bord()
{
    for (i=0; i<=LGMAX; ++i)
    {
        lev[i][0]=i;
    }

    for (j=0; j<=LGMAX; ++j)
    {
        lev[0][j]=j;
    }
}

typ min2(typ x,typ y)
{
    if (x<y) return x;
    return y;
}

typ min3(typ x,typ y,typ z)
{
    typ mn=min2(x,y);
    return min2(z,mn);
}

int main()
{
    nid=1;
    while (fin>>tab[nid]+1)
    {
        ++nid;
    }

    bord();


    for (iid=1; iid<=nid; ++iid)
    {
        lgi=strlen(tab[iid]+1);
        for (jid=iid+1; jid<=nid; ++jid)
        {
            lgj=strlen(tab[jid]+1);


            for (i=1; i<=lgi; ++i)
            {
                for (j=1; j<=lgj; ++j)
                {
                    if (tab[iid][i]==tab[jid][j])
                    {
                        lev[i][j]=lev[i-1][j-1];
                    }
                    else
                    {
                        lev[i][j]=min3(lev[i-1][j-1],lev[i-1][j],lev[i][j-1])+1;
                        if (iid==2 && jid==5)
                        {
                            iid=2;
                        }
                        // jdel=j;
                    }
                }
            }



            if (lev[lgi][lgj]==1)
            {
                i=lgi;
                j=lgj;

                while (i>=1 && j>=1)
                {
                    if (tab[iid][i]==tab[jid][j])
                    {
                        --i;
                        --j;
                    }
                    else
                    {
                        idel=i;
                        break;
                    }
                }
                strcpy(aux,tab[iid]+idel+1);
                strcpy(tab[iid]+idel,aux);

                fout << tab[iid]+1;

                return 0;
            }
        }


    }

    return 0;
}
