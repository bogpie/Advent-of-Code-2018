#include <fstream>

using namespace std;

ifstream fin ("d23.in");
ofstream fout("d23.out");

char chr,vchr[101];
const long long NBOT=1001;
long long x,y,z,nbot,ibot,xstrong,ystrong,zstrong,rstrong,r,rmax,strongbot,nclose,dist;

struct sctbot
{
    long long x,y,z,r;
}
vbot[NBOT+2];

int main()
{
    while (fin>>chr)
    {
        fin >> chr >> chr >> chr >> chr;
        fin >> x >> chr >> y >> chr >> z >> vchr;
        fin >> chr >> chr >> r;
        vbot[nbot].x=x;
        vbot[nbot].y=y;
        vbot[nbot].z=z;
        vbot[nbot].r=r;
        if (r>rmax)
        {
            rmax=r;
            strongbot=nbot;
        }
        ++nbot;
    }
    xstrong=vbot[strongbot].x;
    ystrong=vbot[strongbot].y;
    zstrong=vbot[strongbot].z;
    rstrong=vbot[strongbot].r;

    for (ibot=0;ibot<nbot;++ibot)
    {
        x=vbot[ibot].x;
        y=vbot[ibot].y;
        z=vbot[ibot].z;
        dist=(abs(x-xstrong) + abs(y-ystrong) + abs(z-zstrong));
        if  (dist <= rstrong)
        {
            ++nclose;
        }
    }

    fout << " part one : " << nclose << "\n";

    return 0;
}
