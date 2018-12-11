#include <fstream>
#include <climits>
#include <cmath>

using namespace std;

ifstream fin ("p11.in");
ofstream fout("p11.out");

long long i,j,mxsum,serial,sum,isol,jsol,aux;
long long mpow[302][302];
long long msum[302][302];

long long fsum(long long i,long long j)
{
    long long ret=0;
    for (long long x=i;x<=i+2;++x)
    {
        for (long long y=j;y<=j+2;++y)
        {
            ret+=mpow[x][y];
        }
    }
    return ret;
}

long long fform(long long i,long long j,long long serial)
{

    long long rack=i+10;
    long long cif=( (rack*j+serial)*rack / 100 ) % 10 ;
    cif = abs(cif);
    long long ret=cif-5;

    return ret;

}

int main()
{
    fin >> serial;
    for (i=1;i<=300;++i)
    {
        for (j=1;j<=300;++j)
        {
            mpow[i][j]=fform(i,j,serial);
        }
    }
    mxsum=LONG_LONG_MIN;
    for (i=1;i<=298;++i)
    {
        for (j=1;j<=298;++j)
        {
            sum=msum[i][j]=fsum(i,j);
            if (sum>mxsum)
            {
                mxsum=sum;
                isol=i;
                jsol=j;
            }
        }
    }

   // fout << mpow[122][79] << '\n';
   // fout << mpow[217][196] << '\n';
   // fout << mpow[101][153] << "\n\n";

    fout << mxsum << '\n' << isol << ',' << jsol << '\n';

    return 0;
}
