#include <fstream>
#define intreg long long
#include <algorithm>
#include <cstring>

using namespace std;

ifstream fin("4a.in");
ofstream fout("4a.out");

const intreg NEVENTS=1102,NCHARACTERS=202,NMINUTES=62;
const intreg NGUARDS=10002;
intreg nev,iev,guard,wake,sleep,nap,mxnap,solguard,imin;
intreg iord,mxdays,iguard,solmin;
intreg prod,testdays;
intreg ord[NEVENTS],vnap[NGUARDS];
intreg ndays[NGUARDS][NMINUTES];
char inp[NEVENTS][NCHARACTERS]; // 100;

void sol2()
{
    for (imin=0; imin<60; ++imin)
    {
        for (iguard=1; iguard<=NGUARDS-1; ++iguard)
        {
            testdays=ndays[iguard][imin];
            if (testdays>mxdays)
            {
                mxdays=testdays;
                solmin=imin;
                solguard=iguard;
            }
        }
    }
    prod=solmin*solguard;
    fout << prod;
}

void sol1()
{
    for (iguard=1; iguard<=NGUARDS; ++iguard)
    {
        if (vnap[iguard]>=mxnap)
        {
            mxnap=vnap[iguard];
            solguard=iguard;
        }
    }

    for (imin=0; imin<=59; ++imin)
    {
        if (ndays[solguard][imin]>=mxdays)
        {
            mxdays=ndays[solguard][imin];
            solmin=imin;
        }
    }

    prod=solguard*solmin;

    fout << prod << '\n';
}

void af()
{
    for (intreg i=1; i<=nev; ++i)
    {
        fout << inp[ord[i]] << '\n';
    }
}

void iterate()
{
    for (intreg imin=sleep; imin<wake; ++imin)
    {
        ++ndays[guard][imin];
    }
}

void extract(intreg &var,char evtype)
{
    intreg icar;
    if (evtype=='g')
    {
        for (icar=26; isdigit(inp[iev][icar]); ++icar)
        {
            char car=inp[iev][icar];
            intreg nr=car-'0';
            var=var*10+nr;
        }
    }
    else
    {
        intreg cif1=inp[iev][15]-'0';
        intreg cif2=inp[iev][16]-'0';
        var=cif1*10+cif2;
    }
}

bool isguard()
{
    char car=inp[iev][19];
    if (car=='G')
    {
        return 1;
    }
    return 0;
}
bool issleep()
{
    char car=inp[iev][19];
    if (car=='f')
    {
        return 1;
    }
    return 0;
}

int strcmpp(intreg aa,intreg bb)
{
    intreg lg,lga,lgb,icar;
    lga=strlen(inp[aa]);
    lgb=strlen(inp[bb]);
    lg=min(lga,lgb);
    for (icar=0; icar<lg; ++icar)
    {
        if (inp[aa][icar] < inp[bb][icar])
        {
            return -1;
        }
        if (inp[aa][icar] > inp[bb][icar])
        {
            return 1;
        }
    }
}

bool cmp(intreg a,intreg b)
{
    if (strcmpp(a,b)<0)
    {
        return 1;
    }
    return 0;

}

int main()
{

    while (fin.getline( inp[++nev], NCHARACTERS ) )
    {
        ord[nev]=nev;

    }
    --nev;
    sort (ord+1,ord+nev+1,cmp);

    // af();

    for (iord=1; iord<=nev; ++iord)
    {
        iev=ord[iord];
        if (isguard())
        {
            guard=sleep=wake=0;
            extract(guard,'g');
        }
        else if (issleep())
        {
            extract(sleep,'s');
        }
        else
        {
            extract(wake,'w');
            vnap[guard]+=wake-sleep;

            iterate();
            sleep=wake=0;
        }
    }

    sol1();
    sol2();

}

