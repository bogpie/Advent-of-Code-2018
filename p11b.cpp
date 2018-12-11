#include <fstream>
#include <climits>
#include <cmath>

using namespace std;

ifstream fin ("p11.in");
ofstream fout("p11.out");

const long long n=300;
long long i,j,mxsum,serial,sum,isol,jsol,aux,k,lat,ibot,jbot,ar,latsol,pw;
long long mdin[302][302];
//long long mpow[302][302];

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
    for (i=1;i<=n;++i)
    {
        for (j=1;j<=n;++j)
        {
            pw=fform(i,j,serial);
           // mpow[i][j]=pw;
            mdin[i][j]=pw+mdin[i-1][j]+mdin[i][j-1]-mdin[i-1][j-1];

            if (mdin[i][j]<-1000)
            {
                aux=1;
            }
        }
    }
  //  fout << '\n';
    mxsum=LONG_LONG_MIN;
    for (lat=1;lat<=n;++lat)
    {
        /// jos !!
        for (i=lat;i<=n;++i)
        {
            for (j=lat;j<=n;++j)
            {
                sum=mdin[i][j]-mdin[i-lat][j]-mdin[i][j-lat]+mdin[i-lat][j-lat];
                if (sum>mxsum)
                {
                    mxsum=sum;
                    ibot=i;
                    jbot=j;
                    latsol=lat;
                }
            }
        }
    }
    isol=ibot-latsol+1;
    jsol=jbot-latsol+1;
    //ar=latsol*latsol;

    fout << isol << ',' << jsol << ',' << latsol;

    return 0;
}
