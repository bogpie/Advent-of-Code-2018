#include <fstream>

using namespace std;

ifstream fin ("10.in");
ofstream fout("10.out");

const int NPT=11111,POZMIN=-99999,POZMAX=99999,POZAF=1001;
int x,y,velx,vely,ipt,npt,i,j,sec,xmax,ymax,xmin,ymin;
int xxmin,yymin,xxmax,yymax;
int tab[POZAF][POZAF];
bool isdiez[POZAF][POZAF];
bool stop;

struct sct
{
    int x,y;
} vpoz[NPT],vvel[NPT];

void minimax(int x,int y,int &xmin,int &ymin,int &xmax,int &ymax)
{
    if (x< xmin)
    {
        xmin=x;

    }
    if (y< ymin)
    {
        ymin=y;
    }
    if (x > xmax)
    {
        xmax=x;
    }
    if (y > ymax)
    {
        ymax=y;
    }
}

void af()
{
    int xmin=POZMAX;
    int ymin=POZMAX;
    int xmax=POZMIN;
    int ymax=POZMIN;

    for (int ipt=1; ipt<=npt;++ipt)
    {
        x=vpoz[ipt].x=vpoz[ipt].x-vvel[ipt].x+99999;
        y=vpoz[ipt].y=vpoz[ipt].y-vvel[ipt].y+99999;
        minimax(x,y,xmin,ymin,xmax,ymax);
    }
    for (int ipt=1; ipt<=npt;++ipt)
    {
        x=vpoz[ipt].x=vpoz[ipt].x-xmin;
        y=vpoz[ipt].y=vpoz[ipt].y-ymin;
        isdiez[x][y]=1;
    }
    for (int i=0;i<=POZAF;++i)
    {
        for (int j=0;j<=POZAF;++j)
        {
            if (isdiez[j][i])
            {
                fout << '#';
            }
            else
            {
                fout << '.';
            }
        }
        fout << '\n';
    }
}

char sir[111],car;

int main()
{
    while (fin>>car)
    {
        for (i=1; i<=9; ++i)
        {
            fin >> car;
        }

        fin >> x >> sir >> y >>  sir;

        for (i=1; i<=10; ++i)
        {
            fin >> car;
        }


        fin >> velx >> sir >> vely >> sir;
        vpoz[++ipt].x=x;
        vpoz[ipt].y=y;
        vvel[ipt].x=velx;
        vvel[ipt].y=vely;

        x=vpoz[ipt].x;
        y=vpoz[ipt].y;


        minimax(x,y,xmin,ymin,xmax,ymax);

    }
    npt=ipt;

    xxmin=xmin;
    yymin=ymin;
    xxmax=xmax;
    yymax=ymax;

    sec=0;
    while (sec<99999)
    {
        //stop=0;
        xmin=POZMAX;
        ymin=POZMAX;
        xmax=POZMIN;
        ymax=POZMIN;

        for (ipt=1; ipt<=npt; ++ipt)
        {
            x=vpoz[ipt].x=vpoz[ipt].x+vvel[ipt].x;
            y=vpoz[ipt].y=vpoz[ipt].y+vvel[ipt].y;
            if (x<xmin)
            {
                xmin=x;

            }
            if (y< ymin)
            {
                ymin=y;
            }
            if (x > xmax)
            {
                xmax=x;
            }
            if (y > ymax)
            {
                ymax=y;
            }

        }


        if (xmin<xxmin || ymin<yymin || xmax>xxmax || ymax>yymax)
        {
            fout << sec << '\n';
            af();

            return 0;
        }
        ++sec;
        xxmin=xmin;
        yymin=ymin;
        xxmax=xmax;
        yymax=ymax;

    }

    return 0;
}
