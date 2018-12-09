#include <fstream>
#include <vector>

using namespace std;

ifstream fin ("9.in");
ofstream fout("9.out");

const unsigned long long NELF=502;
unsigned long long nelf,nelem,sol,ielf,imarb,isir,iparc;
unsigned long long vscor[NELF];

char sir[102];

struct elem
{
    long long val;
    elem * dr;
    elem * st;
};

long long fsol(int nelf, long long nelem)
{
    elem * elemcrt = new elem;
    elemcrt->val = 0;
    elemcrt->dr = elemcrt;
    elemcrt->st = elemcrt;

    for (imarb = 1; imarb <= nelem; ++imarb)
    {
        ++ielf;
        if (ielf>nelf)
        {
            ielf=1;
        }
        if (imarb % 23 == 0)
        {
            for (iparc=1;iparc<=7;++iparc)
            {
                elemcrt = elemcrt->st;
            }
            vscor[ielf] += elemcrt->val + imarb;
            elemcrt = elemcrt->dr;
            elemcrt->st = elemcrt->st->st;
            elemcrt->st->dr = elemcrt;
        }
        else
        {
            elem * newelem = new elem;
            newelem->val = imarb;
            newelem->dr = elemcrt->dr->dr;
            newelem->st = elemcrt->dr;
            newelem->dr->st = newelem;
            newelem->st->dr = newelem;
            elemcrt = newelem;
        }
    }

    for (ielf= 1; ielf <= nelf; ++ielf)
    {
        if (vscor[ielf] > sol)
            sol = vscor[ielf];
    }

    return sol;
}

int main ()
{
    fin >> nelf;
    for (isir=1; isir<=5; ++isir)
    {
        fin >> sir;
    }
    fin >> nelem;
    fin >> sir;

    nelem*=100;
    sol=fsol(nelf, nelem);
    fout << sol;
}
