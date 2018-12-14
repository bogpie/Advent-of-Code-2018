#include <fstream>

using namespace std;

ifstream fin ("1b.in");
ofstream fout("1b.out");

long long sum,xmod,imod,nmod;
bool ex[2][1000001];
long long vmod[1000001];

long long mod(int x)
{
    if (x<0)
        return -x;
    return x;
}

int main()
{
    while (fin>>xmod)
    {
        vmod[++nmod]=xmod;
    }

    ex[1][0]=1;
    for (imod=1;imod<=nmod;++imod)
    {
        sum+=vmod[imod];


        if (ex[(sum>=0)][mod(sum)])
        {
            fout << sum;
            return 0;
        }
        ex[(sum>=0)][mod(sum)]=1;
        if (imod==nmod)
        {
            imod=0;
        }
    }

    return 0;
}

