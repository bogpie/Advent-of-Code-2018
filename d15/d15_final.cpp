#include <fstream>
#include <deque>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin ("d15.in");
ofstream fout("d15.out");

const int NLIN=32,NCOL=32,MAXNUM=1100;
int ilin,icol,nround,nunit,iunit,x1,y1,num1,enemy,idir,xx1,yy1;
int vpwr[]={0,3,3};
int venemy[]={0,2,1};
int junit,x2,y2,xx2,yy2,minnum,num2,xnear,ynear,tothp,outcome;
int nlin,ncol,lowhp,lowunit,nelf,ngobl,numold;
int dx[]= {-1,0,0,1};
int dy[]= {0,-1,1,0};
char ch;

bool cmp2(int x1,int y1,int x2,int y2)
{
    if (x1==x2)
    {
        return y1<y2;
    }
    return x1<x2;
}

struct structdeque
{
    int x,y,num;
};

struct structunit
{
    int x,y,num,hp;
};

struct structmatrix
{
    int num;
    char ch;
} mat[NLIN+2][NCOL+2];

deque <structdeque> deq;
vector <structunit> vunit;

void recount(int &numold)
{
    nunit=vunit.size();
    if (numold==-1)
    {
        --nelf;
    }
    else if (numold==-2)
    {
        --ngobl;
    }

}
bool cmp(structunit a,structunit b)
{
    if (a.x==b.x)
    {
        return a.y<b.y;
    }
    return a.x<b.x;
}

void tryattack(int iunit,int &lowunit,int &numold)
{
    int x1=vunit[iunit].x;
    int y1=vunit[iunit].y;
    int num1=vunit[iunit].num;
    int enemy=0;
    if (num1==-1) enemy=-2;
    else enemy=-1;
    lowunit=-1;
    int lowhp=201;
    //sort (vunit.begin(),vunit.end(),cmp);
    for (int junit=0; junit<nunit; ++junit)
    {
        if (vunit[junit].num!=enemy) continue;
        int x2=vunit[junit].x;
        int y2=vunit[junit].y;
        if ( (abs(x2-x1)==1 && y1==y2) || ((abs(y2-y1)==1 && x1==x2)) )
        {
            int hp=vunit[junit].hp;
            if (hp<lowhp)
            {
                lowhp=hp;
                lowunit=junit;
            }
            else if (hp==lowhp)
            {
                if (vunit[junit].x == vunit[lowunit].x)
                {
                    if (vunit[junit].y<vunit[lowunit].y)
                    {
                        lowunit=junit;
                    }
                }
                else if (vunit[junit].x<vunit[lowunit].x)
                {
                    lowunit=junit;
                }
            }
        }
    }
    if (lowunit!=-1)
    {
        num1=vunit[lowunit].num;
        vunit[lowunit].hp-=vpwr[venemy[abs(num1)]];
        if (vunit[lowunit].hp<=0)
        {
            int x2=vunit[lowunit].x;
            int y2=vunit[lowunit].y;
            mat[x2][y2].num=0;
            numold=vunit[lowunit].num;
            vunit.erase(vunit.begin()+lowunit);

        }

    }
}
void lee (int x,int y)
{
    deq.clear();
    deq.push_back({x,y,1});
    int num=mat[x][y].num;
    int enemy;
    if (num==-1) enemy=-2;
    else enemy=-1;
    while (!deq.empty())
    {
        int x=deq.front().x;
        int y=deq.front().y;
        int num=deq.front().num;
        for (int idir=0; idir<4; ++idir)
        {
            int xx=x+dx[idir];
            int yy=y+dy[idir];

            if (xx==0)
            {
                int aux=1;
            }

            if (!mat[xx][yy].num)
            {
                mat[xx][yy].num=num+1;
                deq.push_back({xx,yy,num+1});
            }
        }
        ++num;
        deq.pop_front();
    }
}

void fclear()
{
    for (int ilin=0; ilin<nlin; ++ilin)
    {
        for (int icol=0; icol<ncol; ++icol)
        {
            if (mat[ilin][icol].num>0)
            {
                mat[ilin][icol].num=0;
            }
        }
    }
}

/*
void af()
{
    if (nround>1)
    fout << "After Round" << ' ' << nround-1 << '\n';
    for (int ilin=0; ilin<nlin; ++ilin)
    {
        for (int icol=0; icol<ncol; ++icol)
        {
            int num=mat[ilin][icol].num;
            if (num==-8) fout <<'#';
            else if (num==-1) fout <<'E';
            else if (num==-2) fout <<'G';
            else fout <<'.';
            //fout <<' ';
        }
        fout <<'\n';
    }
    //fout <<'\n';

}

void af3()
{
    //fout << "After Round" << ' ' << nround-1 << '\n';
    for (int iunit=0; iunit<nunit; ++iunit)
    {
        fout << vunit[iunit].hp << '\n';
    }
    fout << '\n';
}

void aflee()
{
    //fout << "After Round" << ' ' << nround-1 << '\n';
    for (int ilin=0; ilin<nlin; ++ilin)
    {

        for (int icol=0; icol<nlin; ++icol)
        {
            if (mat[ilin][icol].num>=0 && mat[ilin][icol].num<=9)
            {
                fout <<' ';
            }
            fout << mat[ilin][icol].num << ' ';

        }
        fout <<'\n';
    }
    fout << '\n';
}

*/

void replaceelfpower(int pwr)
{
    vpwr[1]=pwr;
}

int main()
{
    nlin=NLIN;
    ncol=NCOL;

    //replaceelfpower(11);
    //replaceelfpower(12);
    replaceelfpower(13);

    for (ilin=0; ilin<nlin; ++ilin)
    {
        for (icol=0; icol<ncol; ++icol)
        {
            fin >> ch;
            if (!ch)
            {
                break;
            }
            mat[ilin][icol].ch=ch;
        }
    }

    for (ilin=0; ilin<nlin; ++ilin)
    {
        for (icol=0; icol<ncol; ++icol)
        {
            ch=mat[ilin][icol].ch;
            if (ch=='.') continue;
            if (ch=='#')
            {
                mat[ilin][icol].num=-8;
            }
            else
            {
                if (ch=='E')
                {
                    num1=mat[ilin][icol].num=-1;
                    ++nelf;
                }
                else if (ch=='G')
                {
                    num1=mat[ilin][icol].num=-2;
                    ++ngobl;
                }
                ++nunit;
                vunit.push_back({ilin,icol,num1,200});
            }
        }
    }

    fclear();
    while (1)
    {
        ++nround;
        sort (vunit.begin(),vunit.end(),cmp);


        /*
        if (nround>=1)
        {
             af();
            af3();

        }
        */

         nunit=vunit.size();
        for (iunit=0; iunit<nunit; ++iunit)
        {

            numold=-4;
            lowunit=-1;
            tryattack(iunit,lowunit,numold);
            if (vunit.size()!=nunit)
            {
                recount(numold);

                if (lowunit<iunit)
                {
                    --iunit;
                }
                nunit=vunit.size();

                if (!nelf || !ngobl)
                {
                    //af();
                    //af3();

                    if (iunit!=nunit-1)
                    {
                        --nround;
                    }
                    for (iunit=0; iunit<nunit; ++iunit)
                    {
                        tothp+=vunit[iunit].hp;
                    }
                    outcome=nround*tothp;
                    fout << 10-nelf << '\n';
                    fout << outcome << '\n';
                    return 0;
                }
                continue;
            }
            if (lowunit!=-1)
            {
                continue;
            }

            x1=vunit[iunit].x;
            y1=vunit[iunit].y;
            num1=vunit[iunit].num;
            if (num1==-1) enemy=-2;
            else enemy=-1;


            fclear();

            lee(x1,y1);
           // fout << x1 << ' ' <<y1 << '\n';
           // aflee();

            minnum=MAXNUM;
            xnear=ynear=-1;
            for (junit=0; junit<nunit; ++junit)
            {
                x2=vunit[junit].x;
                y2=vunit[junit].y;
                num2=vunit[junit].num;
                if (num2!=enemy)
                {
                    continue;
                }
                for (idir=0; idir<4; ++idir)
                {
                    xx2=x2+dx[idir];
                    yy2=y2+dy[idir];
                    num2=mat[xx2][yy2].num;
                    if (num2<minnum && num2>0)
                    {
                        minnum=num2;
                        xnear=xx2;
                        ynear=yy2;
                    }
                    else if(num2==minnum)
                    {
                        if (!cmp2(xnear,ynear,xx2,yy2))
                        {
                            xnear=xx2;
                            ynear=yy2;
                        }
                    }
                }

            }
            if (xnear==-1 || ynear==-1)
            {
                continue;
            }
            fclear();

            mat[xnear][ynear].num=-3;
            lee(xnear,ynear);
            mat[xnear][ynear].num=1;
        //fout << xnear << ' ' <<ynear << '\n';
           // aflee();

            minnum=MAXNUM;
            for (idir=0; idir<4; ++idir)
            {
                xx1=x1+dx[idir];
                yy1=y1+dy[idir];
                num1=mat[xx1][yy1].num;
                if (num1<minnum && num1>0)
                {
                    minnum=num1;
                    xnear=xx1;
                    ynear=yy1;
                }
                else if(num2==minnum)
                {
                    if (!cmp2(xnear,ynear,xx1,yy1))
                    {
                        xnear=xx1;
                        ynear=yy1;
                    }
                }
            }

            xx1=vunit[iunit].x=xnear;
            yy1=vunit[iunit].y=ynear;
            mat[xx1][yy1].num=mat[x1][y1].num;
            mat[x1][y1].num=0;

            lowunit=-1;
            numold=-4;
            tryattack(iunit,lowunit,numold);

            if (vunit.size()!=nunit)
            {
                nunit=vunit.size();
                recount(numold);

                if (lowunit<iunit)
                {
                    --iunit;
                }

                if (!nelf || !ngobl)
                {
                    if (iunit!=nunit-1)
                    {
                        --nround;
                    }
                    for (iunit=0; iunit<nunit; ++iunit)
                    {
                        tothp+=vunit[iunit].hp;
                    }
                    outcome=nround*tothp;
                    fout << 10-nelf << '\n';
                    fout << outcome << '\n';
                    return 0;
                }
                continue;
            }


        }
    }

    return 0;
}


