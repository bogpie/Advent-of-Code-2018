#include <fstream>
#include <cstring>

using namespace std;

ifstream fin ("d17.in");
ofstream fout("d17.out");


const int LGSTR=101, XMAX=700,YMAX=2000,NPOINT=1673;
char str[LGSTR+2];
int xmin=XMAX+1,xmax=-1,ymin=YMAX+1,ymax=-1;
int x1,x2,y1,y2,ipoint,npoint,i,j,solsettled,solflowing;
char mat[YMAX+10][XMAX+10];


struct sctpoint
{
    int x1,x2,y1,y2;
} vpoint[NPOINT+2];

void fsol()
{
    for (int j=ymin; j<=ymax; ++j)
    {
        for (int i=0; i<=XMAX+2; ++i)
        {
            if (mat[j][i]=='x')
            {
                ++solsettled;
            }
            if (mat[j][i]=='|')
            {
                ++solflowing;
            }
        }
    }
}

bool isdry(char ch)
{
    if (ch=='x' || ch=='#')
    {
        return 1;
    }
    return 0;
}

void af()
{
    for (int j=ymin; j<=ymax; ++j)
    {
        for (int i=max(xmin-2,0); i<=XMAX+1; ++i)
        {
            fout << mat[j][i] << ' ';
        }
        fout << '\n';
    }
    fout << '\n';
}

void freset()
{
    for (int j=0; j<=YMAX+2; ++j)
    {
        for (int i=0; i<=XMAX+2; ++i)
        {
            mat[j][i]='.';
        }
    }
}

void pour (int y,int x)
{

    if (mat[y+1][x]=='@' || mat[y+1][x]=='|')
    {
        mat[y][x]='|';
        return;
    }

    if (mat[y+1][x]=='.')
    {
        pour(y+1,x);
    }
    if (mat[y+1][x]=='|')
    {
        mat[y][x]='|';
        return;

    }

    int ileft=x-1;
    while (mat[y][ileft]=='.' && isdry(mat[y+1][ileft]))
    {
        --ileft;
    }
    ++ileft;

    int iright=x+1;
    while (mat[y][iright]=='.' && isdry(mat[y+1][iright]))
    {
        ++iright;
    }
    --iright;

    if (isdry(mat[y][ileft-1]) && isdry(mat[y][iright+1]))
    {
        for (int i=ileft; i<=iright; ++i)
        {
            mat[y][i]='x';
        }
        mat[y][x]='x';
    }
    else
    {
        for (int i=ileft; i<=iright; ++i)
        {
            mat[y][i]='|';
        }
        mat[y][x]='|';

        int ileftbak=ileft;
        int irightbak=iright;

        if ( isdry(mat[y][ileft-1]))
        {
            iright=ileft+1;
            while (mat[y][iright]=='|')
            {
                ++iright;
            }
            --iright;
            if (isdry(mat[y][iright+1]))
            {
                for (int i=ileft; i<=iright; ++i)
                {
                    mat[y][i]='x';
                }
            }
        }

        ileft=ileftbak;
        iright=irightbak;


        if ( isdry(mat[y][iright+1]))
        {
            ileft=iright-1;
            while (mat[y][ileft]=='|')
            {
                --ileft;
            }
            ++ileft;
            if (isdry(mat[y][ileft-1]))
            {
                for (int i=ileft; i<=iright; ++i)
                {
                    mat[y][i]='x';
                }
            }
        }

        ileft=ileftbak;
        iright=irightbak;

        if (mat[y][ileft-1]=='.' && isdry(mat[y+1][ileft]))
        {
            pour(y,ileft-1);
        }
        if (mat[y][iright+1]=='.' && isdry(mat[y+1][iright]))
        {
            pour(y,iright+1);
        }
    }
}

void fborder()
{
    for (int j=0; j<=ymax+1; ++j)
    {
        mat[j][0]=mat[j][XMAX+1]='@';
        mat[j][0]=mat[j][XMAX+1]='@';
    }
    for (int i=0; i<=XMAX; ++i)
    {
        mat[ymax+1][i]='@';
    }

}

void fconvert (int &x,int &pozfdigit)
{
    char ch;
    while (isdigit(ch=str[pozfdigit]))
    {
        x=x*10+(ch-'0');
        ++pozfdigit;
    }
}

void fparseline(int &x1,int &x2,int &y1,int &y2)
{
    int pozfdigit=0;
    x1=x2=y1=y2=0;

    char *pt=strchr(str,'=');
    pozfdigit=pt-str+1;


    if (str[0]=='x')
    {
        fconvert(x1,pozfdigit);
        x2=x1;
        pt=strchr(pt+1,'=');
        pozfdigit=pt-str+1;
        fconvert(y1,pozfdigit);
        pozfdigit+=2;
        fconvert(y2,pozfdigit);
    }
    else
    {
        fconvert(y1,pozfdigit);
        y2=y1;
        pt=strchr(pt+1,'=');
        pozfdigit=pt-str+1;
        fconvert(x1,pozfdigit);
        pozfdigit+=2;
        fconvert(x2,pozfdigit);
    }



}



int main()
{
    while (fin.getline(str,LGSTR))
    {
        fparseline(x1,x2,y1,y2);
        vpoint[ipoint].x1=x1;
        vpoint[ipoint].x2=x2;
        vpoint[ipoint].y1=y1;
        vpoint[ipoint++].y2=y2;

        if (x1<xmin)
        {
            xmin=x1;
        }
        if (y1<ymin)
        {
            ymin=y1;
        }
        if (x2>xmax)
        {
            xmax=x2;
        }
        if (y2>ymax)
        {
            ymax=y2;
        }
    }
    freset();
    fborder();
    mat[0][500]='+';
    npoint=ipoint;
    for (ipoint=0; ipoint<npoint; ++ipoint)
    {
        x1=vpoint[ipoint].x1;
        x2=vpoint[ipoint].x2;
        y1=vpoint[ipoint].y1;
        y2=vpoint[ipoint].y2;
        for (j=y1; j<=y2; ++j)
        {
            for (i=x1; i<=x2; ++i)
            {
                mat[j][i]='#';
            }
        }
    }

    // af();
    pour(1,500);
    mat[0][500]='+';
    af();

    fsol();
    fout << "p1: " << solsettled+solflowing << '\n';
    fout << "p2: " << solsettled << '\n';

    return 0;
}
