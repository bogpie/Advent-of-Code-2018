#include <fstream>
#include <cstring>

using namespace std;

ifstream fin ("d20.in");
ofstream fout("d20.out");

const int NCHR=14230,ADD=101;
int ichr,length,nchr,sol,istack,xmax,ymax,sol2,ilin,icol;
int xmin=NCHR+2;
int ymin=NCHR+2;
char vchr[NCHR+2];
int matdist[ADD*2+2][ADD*2+2];

bool iscoord (char chr)
{
    if (chr=='N' || chr=='E' || chr=='W' || chr=='S')
    {
        return 1;
    }
    return 0;
}

struct sctpoint
{
    int x,y,length;
}vstack[NCHR+2],vdir[302];

void initcoorddir()
{
    vdir['N'].x=-1;
    vdir['S'].x=+1;
    vdir['W'].y=-1;
    vdir['E'].y=+1;
}

void fminmax(int xx,int yy)
{
    if (xx<xmin)
    {
        xmin=xx;
    }
    if (xx>xmax)
    {
        xmax=xx;
    }
    if (yy<ymin)
    {
        ymin=yy;
    }
    if (yy>ymax)
    {
        ymax=yy;
    }
}

int main()
{
    initcoorddir();
    fin.getline(vchr,NCHR);
    vchr[0]='(';
    nchr=strlen(vchr);
    vchr[nchr-1]=')';
    ++istack;
    ichr=1;

    while (istack)
    {
        while (iscoord(vchr[ichr]))
        {
            vstack[istack].x+=vdir[vchr[ichr]].x;
            vstack[istack].y+=vdir[vchr[ichr]].y;
            fminmax(vstack[istack].x,vstack[istack].y);
            ++vstack[istack].length;
            if (matdist[vstack[istack].x+ADD][vstack[istack].y+ADD])
            {
                if (vstack[istack].length < matdist[vstack[istack].x+ADD][vstack[istack].y+ADD] )
                {
                    matdist[vstack[istack].x+ADD][vstack[istack].y+ADD] = vstack[istack].length;
                }
            }
            else
            {
                matdist[vstack[istack].x+ADD][vstack[istack].y+ADD] = vstack[istack].length;
            }

            ++ichr;
        }

        if (vchr[ichr]=='|')
        {
            if (vchr[ichr+1]==')')
            {
                --istack;
                ichr+=2;
            }
            else
            {
                vstack[istack]=vstack[istack-1];
                ++ichr;
            }
        }
        else if (vchr[ichr]=='(')
        {
            vstack[istack+1]=vstack[istack];
            ++istack;
            ++ichr;
        }
        else
        {
            --istack;
            ++ichr;
        }
    }

    fout << " min x,y ; max x,y  : " << '\n' << xmin << ' ' << ymin <<" ; "<<xmax<<' ' <<ymax << '\n';

    for (ilin=0;ilin<=ADD*2;++ilin)
    {
        for (icol=0;icol<=ADD*2;++icol)
        {
            if (matdist[ilin][icol]>=1000)
            {
                ++sol2;
            }
        }
    }

    fout << "\n part 2 : " << sol2 << '\n';

    return 0;
}
