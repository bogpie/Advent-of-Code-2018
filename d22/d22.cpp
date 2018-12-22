#include <fstream>
#include <set>
#include <utility>
#include <tuple>
#include <climits>
#define data long long
#define mkp make_pair

using namespace std;

ifstream fin ("d22.in");
ofstream fout("d22.out");


char vchr[101],vdraw[10],chr;
const data NLIN=780,NCOL=15,COLZERO=48271, LINZERO=16807,MOD=20183, TIMEMAX=INT_MAX;
const data LINLIMIT=1000, COLLIMIT=1000,NTOOLS=3;
data matlevel[LINLIMIT+1][COLLIMIT+1], matregtype[LINLIMIT+1][COLLIMIT+1];
data coltarget,lintarget,icol,ilin,depth,level,tlinpe,totrisk,geo,itool;
data col,lin,colnew,linnew,timenew,tool,idir,time,regtype,toolnew,timeold,toolold;

data mattime[LINLIMIT+1][COLLIMIT+1][NTOOLS+1];
bool isbrowsed[LINLIMIT+1][COLLIMIT+1][NTOOLS+1];

struct sctpoint
{
    data lin,col,tool,time;
} vdir[10];
sctpoint point;

set < pair <data, tuple <data,data,data> > > squ;

void setdir()
{
    vdir[0].lin=-1;
    vdir[0].col= 0;
    vdir[1].lin= 0;
    vdir[1].col=+1;
    vdir[2].lin=+1;
    vdir[2].col= 0;
    vdir[3].lin= 0;
    vdir[3].col=-1;
}

data ad (data x, data y)
{
    return ( x % MOD + y % MOD ) % MOD;
}
data mult (data x, data y)
{
    return ( x % MOD * y % MOD ) % MOD;
}
void setvdraw()
{
    vdraw[0]='.';
    vdraw[1]='=';
    vdraw[2]='|';
}

void af()
{
    for (int ilin=0; ilin<=LINLIMIT; ++ilin)
    {
        for (int icol=0; icol<=COLLIMIT; ++icol)
        {
            regtype=matregtype[ilin][icol];
            fout << vdraw[matregtype[ilin][icol]];
        }
        fout << '\n';
    }
}



int main()
{
    setvdraw();
    setdir();
    fin >> vchr >> depth >> vchr >> coltarget >> chr >> lintarget;
    matlevel[0][0]=ad(geo,depth);

    for (ilin=1; ilin<=LINLIMIT; ++ilin)
    {
        geo=mult(ilin,COLZERO);
        level = matlevel[ilin][0] = ad (geo, depth );
        regtype = level%3;
        matregtype[ilin][0]=regtype;
    }

    for (icol=1; icol<=COLLIMIT; ++icol)
    {
        geo= mult(icol,LINZERO) ;
        level = matlevel[0][icol] = ad (geo, depth );
        regtype = level%3;
        matregtype[0][icol]=regtype;
    }

    for (ilin=1; ilin<=LINLIMIT; ++ilin)
    {
        for (icol=1; icol<=COLLIMIT; ++icol)
        {
            if (ilin==lintarget && icol==coltarget)
            {
                geo=0;
            }
            else
            {
                geo=mult( matlevel[ilin-1][icol],matlevel[ilin][icol-1] );
            }
            level=matlevel[ilin][icol]=ad(geo,depth);
            regtype = level%3;
            matregtype[ilin][icol]=regtype;
        }
    }

    //af();


    for (ilin=0; ilin<=lintarget; ++ilin)
    {
        for (icol=0; icol<=coltarget; ++icol)
        {
            regtype=matregtype[ilin][icol];
            totrisk+=regtype;
        }
    }
    fout << " part one : " << totrisk << "\n";

    squ.insert(make_pair(0,make_tuple(0,0,1)));

    while (!squ.empty() && !isbrowsed[lintarget][coltarget][1])
    {
        time=squ.begin()->first;
        lin=get<0>(squ.begin()->second);
        col=get<1>(squ.begin()->second);
        tool=get<2>(squ.begin()->second);
        squ.erase(squ.begin());

        if(isbrowsed[lin][col][tool])
        {
            continue;
        }

        isbrowsed[lin][col][tool]=1;
        mattime[lin][col][tool]=time;

        for (idir=0;idir<4;++idir)
        {
            linnew=lin+vdir[idir].lin;
            colnew=col+vdir[idir].col;
            timenew=time+1;

            if (linnew>=0 && colnew>=0 && tool!=matregtype[linnew][colnew] && !isbrowsed[linnew][colnew][tool])
            {
                squ.insert(make_pair(timenew,make_tuple(linnew,colnew,tool)));
            }
        }

        for (itool=0;itool<3;++itool)
        {
            timenew=time+7;
            if (itool!=tool && itool!=matregtype[lin][col] && !isbrowsed[lin][col][itool])
            {
                squ.insert(make_pair(timenew,make_tuple(lin,col,itool)));
            }

        }
    }

    fout << " part two : " << mattime[lintarget][coltarget][1] << "\n";

    return 0;
}
