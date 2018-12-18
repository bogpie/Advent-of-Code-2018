#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

ifstream fin ("d16.in");
ofstream fout ("d16.out");

int vreg[5],vregafter[5],vregbak[5],a,b,c,unknownoper,nmatch,ireg;
int solone,imatch,voper[20],ioper,noper,eraseop,niterations,joper,actualoper;
char sir[102],chr;
bool eqreg;
vector <int> tabid[20];
vector <int>::iterator it;

void addr(int a,int b,int c)
{
    vreg[c]=vreg[a]+vreg[b];
}

void addi(int a,int b,int c)
{
    vreg[c]=vreg[a]+b;
}

void mulr(int a,int b,int c)
{
    vreg[c]=vreg[a]*vreg[b];
}


void muli(int a,int b,int c)
{
    vreg[c]=vreg[a]*b;
}

void banr(int a,int b,int c)
{
    int tleft=vreg[a] & vreg[b];
    vreg[c]=tleft;
}

void bani(int a,int b,int c)
{
    int tleft = vreg[a] & b;
    vreg[c]=tleft;
}


void borr(int a,int b,int c)
{
    int tleft = vreg[a] | vreg[b];
    vreg[c]=tleft;
}

void bori(int a,int b,int c)
{
    int tleft = vreg[a] | b;
    vreg[c]=tleft;
}

void setr(int a,int b,int c)
{
    vreg[c]=vreg[a];
}

void seti(int a,int b,int c)
{
    vreg[c]=a;
}

void gtir(int a,int b,int c)
{
    vreg[c]=(a>vreg[b]);
}

void gtri(int a,int b,int c)
{
    vreg[c]=(vreg[a]>b);
}

void gtrr(int a,int b,int c)
{
    vreg[c]=(vreg[a]>vreg[b]);
}

void eqir(int a,int b,int c)
{
    vreg[c]=(a==vreg[b]);
}

void eqri(int a,int b,int c)
{
    vreg[c]=(vreg[a]==b);
}

void eqrr(int a,int b,int c)
{
    vreg[c]=(vreg[a]==vreg[b]);
}


void foper(int ioper,int a,int b,int c)
{
    int joper=0;

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


bool testeqreg()
{
    for (int ireg=0;ireg<=3;++ireg)
    {
        if (vreg[ireg]!=vregafter[ireg])
        {
            return 0;
        }
    }
    return 1;
}

void findnmatch(int a,int b,int c,int &nmatch,int unknownoper)
{
    for (int ioper=0; ioper<=15; ++ioper)
    {
        for (ireg=0;ireg<=3;++ireg)
        {
            vreg[ireg]=vregbak[ireg];
        }

        foper(ioper,a,b,c);

        if (!testeqreg())
        {
            continue;
        }

        ++nmatch;
        if ( find(tabid[ioper].begin(), tabid[ioper].end(), unknownoper) == tabid[ioper].end() )
        {
            tabid[ioper].push_back(unknownoper);
        }

    }

}

int main()
{
    while (fin>>sir)
    {
        if (sir[0]!='B')
        {
            break;
        }
        fin >> chr >> vreg[0] >> chr >> vreg[1] >> chr >> vreg[2] >> chr >> vreg[3] >> chr;
        for (ireg=0;ireg<=3;++ireg)
        {
            vregbak[ireg]=vreg[ireg];
        }
        fin >> unknownoper >> a >> b >> c;
        fin >> sir >> chr >> vregafter[0] >> chr >> vregafter[1] >> chr >> vregafter[2] >> chr >> vregafter[3] >> chr;
        nmatch=0;
        findnmatch(a,b,c,nmatch,unknownoper);
        if (nmatch>=3)
        {
            ++solone;
        }
    }

    fout << "p 1 : " << solone << "\n\n";

    for (ioper=0; ioper<16; ++ioper)
    {
        sort (tabid[ioper].begin(),tabid[ioper].end());
    }


    while (niterations<16)
    {
        for (ioper=0; ioper<16; ++ioper)
        {
            if (tabid[ioper].size()==1)
            {
                eraseop=tabid[ioper][0];
                for (joper=0; joper<16; ++joper)
                {
                    if (joper==ioper) continue;
                    it=find(tabid[joper].begin(),tabid[joper].end(),eraseop);
                    if (it==tabid[joper].end()) continue;
                    tabid[joper].erase(it);
                }
            }
        }
        ++niterations;
    }


    for (ioper=0; ioper<16; ++ioper)
    {
        voper[tabid[ioper][0]]=ioper;
        fout << "oper " << ioper << " - opcode " << tabid[ioper][0] <<"\n";
    }
    fout <<"\n";

    if (strlen(sir)==1)
    {
        ioper=sir[0]-'0';
    }
    else ioper=(sir[0]-'0')*10+(sir[1]-'0');

    for (ireg=0;ireg<=3;++ireg)
    {
        vreg[ireg]=0;
    }

    fin >> a >> b >> c;
    actualoper=voper[ioper];
    foper(actualoper,a,b,c);

    while (fin >> ioper)
    {
        fin >> a >> b >> c;
        actualoper=voper[ioper];
        foper(actualoper,a,b,c);
    }

    fout << "p 2: " << vreg[0] << '\n';

    return 0;

}
