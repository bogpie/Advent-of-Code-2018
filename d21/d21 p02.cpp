#include <fstream>
#include <climits>
#include <set>

using namespace std;

ifstream fin ("d21.in");
ofstream fout("d21.out");


const long long LGSTR=101,NREG=7,NEVENT=101;
char str[LGSTR+2];
long long vreg[NREG+2],ireg,naf,idiv,three,mxthree,ninstr;
long long regbound,ioper,a,b,c,ip,nevent,val,num,sum,oldthree;
bool isprinted[99999999999];
set <long long> st;
set <long long>::iterator pt;



struct sctevent
{
    long long ioper,a,b,c;
} vevent[NEVENT+2];


void addr(long long a,long long b,long long c)
{
    vreg[c]=vreg[a]+vreg[b];
}

void addi(long long a,long long b,long long c)
{
    vreg[c]=vreg[a]+b;
}

void mulr(long long a,long long b,long long c)
{
    vreg[c]=vreg[a]*vreg[b];
}


void muli(long long a,long long b,long long c)
{
    vreg[c]=vreg[a]*b;
}

void banr(long long a,long long b,long long c)
{
    long long tleft=vreg[a] & vreg[b];
    vreg[c]=tleft;
}

void bani(long long a,long long b,long long c)
{
    long long tleft = vreg[a] & b;
    vreg[c]=tleft;
}


void borr(long long a,long long b,long long c)
{
    long long tleft = vreg[a] | vreg[b];
    vreg[c]=tleft;
}

void bori(long long a,long long b,long long c)
{
    long long tleft = vreg[a] | b;
    vreg[c]=tleft;
}

void setr(long long a,long long b,long long c)
{
    vreg[c]=vreg[a];
}

void seti(long long a,long long b,long long c)
{
    vreg[c]=a;
}

void gtir(long long a,long long b,long long c)
{
    vreg[c]=(a>vreg[b]);
}

void gtri(long long a,long long b,long long c)
{
    vreg[c]=(vreg[a]>b);
}

void gtrr(long long a,long long b,long long c)
{
    vreg[c]=(vreg[a]>vreg[b]);
}

void eqir(long long a,long long b,long long c)
{
    vreg[c]=(a==vreg[b]);
}

void eqri(long long a,long long b,long long c)
{
    vreg[c]=(vreg[a]==b);
}

void eqrr(long long a,long long b,long long c)
{
    vreg[c]=(vreg[a]==vreg[b]);
}


void foper(long long ioper,long long a,long long b,long long c)
{
    long long joper=0;

    if(ioper==joper++)
    {
        addr(a,b,c);
    }

    else if(ioper==joper++)
    {
        addi(a,b,c);
    }

    else if(ioper==joper++)
    {
        mulr(a,b,c);
    }

    else if(ioper==joper++)
    {
        muli(a,b,c);
    }

    else if(ioper==joper++)
    {
        banr(a,b,c);

    }

    else if(ioper==joper++)
    {
        bani(a,b,c);
    }

    else if(ioper==joper++)
    {
        borr(a,b,c);
    }

    else if(ioper==joper++)
    {
        bori(a,b,c);
    }

    else if(ioper==joper++)
    {
        setr(a,b,c);
    }

    else if(ioper==joper++)
    {
        seti(a,b,c);
    }

    else if(ioper==joper++)
    {
        gtir(a,b,c);
    }

    else if(ioper==joper++)
    {
        gtri(a,b,c);
    }

    else if(ioper==joper++)
    {
        gtrr(a,b,c);
    }

    else if(ioper==joper++)
    {
        eqir(a,b,c);
    }

    else if(ioper==joper++)
    {
        eqri(a,b,c);
    }

    else if(ioper==joper++)
    {
        eqrr(a,b,c);
    }

}

void parseline (long long &ioper,long long &a,long long &b,long long &c)
{
    ioper=0;
    if (str[0]=='a')
    {
        if (str[3]=='r')
        {
            ioper=0;
        }
        else ioper=1;
    }
    else if (str[0]=='m')
    {
        if (str[3]=='r')
        {
            ioper=2;
        }
        else ioper=3;
    }
    else if (str[0]=='b')
    {
        if (str[1]=='a')
        {
            if (str[3]=='r')
            {
                ioper=4;
            }
            else ioper=5;
        }
        else
        {
            if (str[3]=='r')
            {
                ioper=6;
            }
            else ioper=7;
        }
    }

    else if (str[0]=='s')
    {
        if (str[3]=='r')
        {
            ioper=8;
        }
        else ioper=9;
    }

    else if (str[0]=='g')
    {
        if (str[2]=='i')
        {
            ioper = 10;
        }
        else
        {
            if (str[3]=='i')
                ioper=11;
            else
                ioper=12;
        }
    }

    else
    {
        if (str[2]=='i')
        {
            ioper = 13;
        }
        else
        {
            if (str[3]=='i')
                ioper=14;
            else
                ioper=15;
        }
    }

    fin >> a >> b >> c;
}


int main()
{
    fin.getline(str,LGSTR);
    regbound=str[4]-'0';

    while (fin>>str)
    {
        parseline(ioper,a,b,c);
        vevent[nevent].ioper=ioper;
        vevent[nevent].a=a;
        vevent[nevent].b=b;
        vevent[nevent].c=c;
        nevent++;
    }

    val=0;
    vreg[0]=val;
    ip=0;
   // mxthree=3173684;

    while (ip<nevent)
    {
        vreg[regbound]=ip;
        ioper=vevent[ip].ioper;
        a=vevent[ip].a;
        b=vevent[ip].b;
        c=vevent[ip].c;

        foper(ioper,a,b,c);
        ip=vreg[regbound];
        if (ip==28) //eqrr 3 0 4
        {

            for (ireg=0;ireg<=5;++ireg)
            {
                fout << vreg[ireg]<<' ';
            }
            fout <<'\n';

            oldthree=three;
            three=vreg[3];
            if (isprinted[three])
            {
                break;
            }
            isprinted[three]=1;
        }
        ++ip;
    }

    fout << "part two : " << oldthree ;

    return 0;
}
