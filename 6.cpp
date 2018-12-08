#include <fstream>
#include <cmath>

using namespace std;

ifstream fin ("6.in");
ofstream fout ("6.out");

const int NMAX=400,DMAX=200000,NID=52,LIMDIST=10000;
int x,y,xx,yy,nid,id,i,j,dist,sol,nlit,maxlit,aux,arreg;
int mid[NMAX+3][NMAX+3],msol[NMAX+3][NMAX+3];
int mdist[NMAX+3][NMAX+3][NMAX+3];

bool chid[NMAX+3][NMAX+3];
bool binf[NMAX+3];
char virg;
struct sct
{
    int x,y;
} vdir[6],qu[DMAX],inp[NID];

int dtot(int i,int j)
{
    int dsol=0;
    for (int id=1;id<=nid;++id)
    {
        int xid=inp[id].x;
        int yid=inp[id].y;
        dsol+= (abs(i-xid) + abs(j-yid));
    }
    return dsol;
}

bool inside(int xx,int yy)
{
    if ( xx>=0 && xx<=NMAX && yy>=0 && yy<=NMAX )
    {
        return 1;
    }
    return 0;
}

void fil (int x, int y, int id,int &nlit)
{
    chid[x][y]=1;

    for (int idir=1; idir<=4; ++idir)
    {
        int xx=x+vdir[idir].x;
        int yy=y+vdir[idir].y;
        if (mid[xx][yy]==id && !chid[xx][yy])
        {
            ++nlit;
            fil(xx,yy,id,nlit);
        }
    }
}

void fqu(int x,int y,int id,int pas)
{
    int p=1;
    int u=0;
    qu[++u].x=x;
    qu[  u].y=y;

    while (p<=u)
    {
        x=qu[p].x;
        y=qu[p].y;
        for (int idir=1; idir<=4; ++idir)
        {
            int xx=x+vdir[idir].x;
            int yy=y+vdir[idir].y;

            if (!inside(xx,yy) || mdist[id][xx][yy]) continue;

            mdist[id][xx][yy]=mdist[id][x][y]+1;
            qu[++u].x=xx;
            qu[  u].y=yy;
        }
        ++p;
    }

}


/*
void fbrd(int mat[NMAX][NMAX])
{
    for (int i=0;i<=NMAX;++i)
    {
        mat[i][0]=mat[i][NMAX-1]=mat[0][i]=mat[NMAX-1][i]=-1;
    }
}
*/

void fmin()
{
    for (int i=0; i<=NMAX; ++i)
        for (int j=0; j<=NMAX; ++j)
        {
            msol[i][j]=DMAX;
        }
}

void fdir()
{
    vdir[1].x=-1;
    vdir[1].y= 0;
    vdir[2].y=-1;
    vdir[2].x= 0;
    vdir[3].x= 1;
    vdir[3].y= 0;
    vdir[4].y= 1;
    vdir[4].x= 0;
}

int main()
{
    fdir();

    /*
        for (i=1;i<=NMAX-1;++i)
        {
          fbrd(mdist[i]);
        }

        fbrd(mid);
    */

    fmin();

    while (fin>>y)
    {
        fin >> virg >> x;
        ++nid;
        inp[nid].x=x;
        inp[nid].y=y;
        mdist[nid][x][y]=1;
        fqu(x,y,nid,1);
    }


    for (i=0; i<=NMAX; ++i)
    {
        for (j=0; j<=NMAX; ++j)
        {
            for (id=1; id<=nid; ++id)
            {
                sol=msol[i][j];
                dist=mdist[id][i][j];
                if (dist<sol)
                {
                    msol[i][j]=mdist[id][i][j];
                    mid[i][j]=id;
                }
                else if(dist==sol)
                {
                    mid[i][j]=-1;
                }

            }
        }
    }


    for (i=0; i<=NMAX; ++i)
    {
        binf[mid[i][0]]=binf[mid[i][NMAX]]=1;
        binf[mid[0][i]]=binf[mid[NMAX][i]]=1;
    }

    for (i=1; i<=NMAX; ++i)
    {
        for (j=1; j<=NMAX; ++j)
        {
            id=mid[i][j];
            if(id && id!=-1 && !chid[i][j] && !binf[id])
            {
                chid[i][j]=1;
                nlit=1;
                fil(i,j,id,nlit);
                if (nlit>maxlit)
                {
                    maxlit=nlit;
                }
            }
        }
    }

    fout << maxlit << '\n';

    for (i=0;i<=NMAX;++i)
    {
        for (j=0;j<=NMAX;++j)
        {
            if (dtot(i,j)<LIMDIST)
            {
                ++arreg;
            }
        }
    }

    fout << arreg;

    return 0;
}

