#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;

ifstream fin ("d13.in");
ofstream fout("d13.out");

const int NLINES=160,NCOLS=160,NCARTS=29,NCH=500;

char world[NLINES+1][NCOLS+1],stcart[]="^,v,>,<", vcartline[NCH];
char kind,kindnew,ch;

int dx[]= {-1,1,0, 0}, dy[]= { 0,0,1,-1},nbroke;
int vcartdir[NCH];
int i,j,length,ncart,icart, xx,yy,x,y,mem,dir;
int ticks,jcart,x1,x2,y1,y2;

bool iscart[NCH+1],part1done,cont;

struct cartstruct
{
    int x,y,mem,ticks;
    char kind;
} vcart[NCARTS];

bool cmp(cartstruct a,cartstruct b) /// for sorting
{
    if (a.x==b.x)
    {
        return a.y<b.y;
    }

    return a.x<b.x;
}

void takeout (int delcart) /// remove function
{
    vcart[delcart].x=vcart[delcart].y=0;
    vcart[delcart].mem=vcart[delcart].ticks=0;
    vcart[delcart].kind='\0';

    for (int icart=delcart+1; icart<ncart; ++icart)
    {
        swap(vcart[icart],vcart[icart-1]);
    }
    --ncart;
}
char fmemkind (int mem,char kind) /// each cart has a 'memory' of where it should go when it reaches '+' intersections. i configured the ways for each case
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

char fturnkind(char slash,char kind) /// replace cart based on corner(slash) and the kind of cart (<,>,v or ^)
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

void setiscart()
{
    iscart['v']=1;
    iscart['^']=1;
    iscart['>']=1;
    iscart['<']=1;
}

void setcartdir() // each cart type has a specific direction,0 is north/up, 1 is south, 2 west, 3 east
{
    vcartdir['<']=3;
    vcartdir['>']=2;
    vcartdir['v']=1;
    vcartdir['^']=0;

}


int main()
{
    setiscart(); /// create a bool vector, an element has true value if it is a cart
    setcartline(); /// used to replace input's carts with the surface underneath
    setcartdir(); /// assign a direction to each cart. 0 is north/up, 1 is south, 2 west, 3 east

    i=j=0;
    while (fin.getline(world[i],201)) /// read each line 
    {
        length=strlen(world[i]);
        for (j=0; j<length; ++j)
        {
            ch=world[i][j];
            if (iscart[ch]) /// if the character is a symbol of a cart
            {
                vcart[icart].x=i;
                vcart[icart].y=j;
                kind=vcart[icart].kind=ch; /// the kind of cart, <,>,^, or v
                world[i][j]=vcartline[ch]; /// replace carts with lines in the input
                ++icart;
            }
        }
        ++i;
    }
    ncart=icart;
    while (1)
    {
        sort (vcart,vcart+ncart,cmp); /// sort carts

        ++ticks;

        icart=0;
        while (icart<ncart) /// for each cart left
        {
            if (vcart[icart].ticks==ticks) /// if we've already moved the cart, move on to the next cart
            {
                ++icart;
                continue;
            }

            x=vcart[icart].x;
            y=vcart[icart].y;
            kind=vcart[icart].kind;
            dir=vcartdir[kind];
            vcart[icart].x=xx=x+dx[dir];
            vcart[icart].y=yy=y+dy[dir]; /// move the cart
            vcart[icart].ticks=ticks;
            ch=world[xx][yy];

            cont=0;
            for (jcart=0;jcart<ncart;++jcart)
            {
                if (jcart==icart)
                {
                    continue;
                }
                if (vcart[jcart].x!=xx || vcart[jcart].y!=yy)
                {
                    continue;
                }

                if (!part1done)
                {
                    fout << "part 1: " << yy << ',' << xx << '\n' ; //return 0;
                    part1done=1;
                }

                takeout(max(icart,jcart));
                takeout(min(jcart,icart)); /// remove the carts
                icart=0; /// reset the cart counter
                cont=1;
                break;
            }
            if (cont)
            {
                continue;
            }


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

        }


        if (ncart==1) /// one cart left, print its coordinates
        {
            fout << "part 2: " << vcart[0].y << ',' << vcart[0].x <<'\n';
            return 0;
        }

    }

    return 0;
}
