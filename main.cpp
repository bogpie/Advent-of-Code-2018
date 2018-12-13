#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;

ifstream fin ("p13.in");
ofstream fout("p13.out");

const int NLINES=160,NCOLS=160,NCARTS=29,NCH=500;

char world[NLINES+1][NCOLS+1],stcart[]="^,v,>,<", vcartline[NCH];
char kind,kindnew,ch;

int dx[]= {-1,1,0, 0}, dy[]= { 0,0,1,-1},nbroke;
int vcartdir[NCH],already[NLINES][NCOLS];
int i,j,length,ncart,icart, xx,yy,x,y,mem,dir;
int steps,jcart,x1,x2,y1,y2;

bool bcart[NCH+1];

struct sct
{
    int x,y,mem,steps;
    char kind;
} vcart[NCARTS];

bool cmp(sct a,sct b)
{
    if (a.x==b.x)
    {
        return a.y<b.y;
    }

    return a.x<b.x;
}

void takeout (int delcart)
{
    vcart[delcart].x=vcart[delcart].y=0;
    vcart[delcart].mem=vcart[delcart].steps=0;
    vcart[delcart].kind='\0';

    for (int icart=delcart+1; icart<ncart; ++icart)
    {
        swap(vcart[icart],vcart[icart-1]);
    }
    --ncart;
}
char fmemkind (int mem,char kind)
{
    if (kind=='<')
    {
        if (mem==0)
        {
            return 'v';
        }
        else if (mem==2)
        {
            return '^';
        }
        return kind;
    }
    if (kind=='>')
    {
        if (mem==0)
        {
            return '^';
        }
        else if (mem==2)
        {
            return 'v';
        }
        return kind;
    }
    if (kind=='v')
    {
        if (mem==0)
        {
            return '>';
        }
        else if (mem==2)
        {
            return '<';
        }
        return kind;
    }
    if (kind=='^')
    {
        if (mem==0)
        {
            return '<';
        }
        else if (mem==2)
        {
            return '>';
        }
        return kind;
    }
}

char fturnkind(char slash,char kind)
{
    if (kind=='>')
    {
        if (slash=='/')
        {
            return '^';
        }
        return 'v';
    }
    if (kind=='<')
    {
        if (slash=='/')
        {
            return 'v';
        }
        return '^';
    }
    if (kind=='v')
    {
        if (slash=='/')
        {
            return '<';
        }
        return '>';
    }
    if (kind=='^')
    {
        if(slash=='/')
        {
            return '>';
        }
        return '<';
    }
}

void setcartline()
{
    vcartline['^']=vcartline['v']='|';
    vcartline['>']=vcartline['<']='-';
}

void setbcart()
{
    bcart['v']=1;
    bcart['^']=1;
    bcart['>']=1;
    bcart['<']=1;
}

void setcartdir()
{
    vcartdir['<']=3;
    vcartdir['>']=2;
    vcartdir['v']=1;
    vcartdir['^']=0;

}


int main()
{
    setbcart();
    setcartline();
    setcartdir();

    for (i=0; i<NLINES; ++i)
    {
        for (j=0; j<NCOLS; ++j)
        {
            already[i][j]=-1;
        }
    }
    i=j=0;
    while (fin.getline(world[i],201))
    {
        length=strlen(world[i]);
        for (j=0; j<length; ++j)
        {
            ch=world[i][j];
            if (bcart[ch])
            {
                vcart[icart].x=i;
                vcart[icart].y=j;
                already[i][j]=icart;
                kind=vcart[icart].kind=ch;
                world[i][j]=vcartline[ch];
                ++icart;
            }
        }
        ++i;
    }
    ncart=icart;
    sort (vcart,vcart+ncart,cmp);
    while (1)
    {
        sort (vcart,vcart+ncart,cmp);

        ++steps;

        if (ncart==1)
        {
            fout <<vcart[0].y << ',' <<vcart[0].x<<'\n';
            return 0;
        }


        icart=0;
        while (icart<ncart)
        {
            if (vcart[icart].steps==steps)
            {
                ++icart;
                continue;
            }

            x=vcart[icart].x;
            y=vcart[icart].y;
            kind=vcart[icart].kind;
            dir=vcartdir[kind];
            vcart[icart].x=xx=x+dx[dir];
            vcart[icart].y=yy=y+dy[dir];
            vcart[icart].steps=steps;
            ch=world[xx][yy];

            already[x][y]=-1;

            if (already[xx][yy]>=0)
            {

                jcart=already[xx][yy];
                already[xx][yy]=-1;

              ///  fout << "part1: " << yy << ',' << xx ; return 0;

                takeout(max(icart,jcart));
                takeout(min(jcart,icart));
                sort (vcart,vcart+ncart,cmp);
                icart=0;
                continue;
            }

            already[xx][yy]=icart;

            if (ch=='+')
            {
                kind=vcart[icart].kind;
                mem=vcart[icart].mem;
                vcart[icart].mem=(vcart[icart].mem+1)%3;
                vcart[icart].kind=kindnew=fmemkind(mem,kind);
            }
            else if (!(ch=='-' || ch=='|'))
            {
                kind=vcart[icart].kind;
                vcart[icart].kind=kindnew=fturnkind(ch,kind);
            }

            ++icart;

            if (ncart==1)
            {
                fout << vcart[0].y << ',' << vcart[0].x <<'\n';
                return 0;
            }
        }


    }

    return 0;
}

