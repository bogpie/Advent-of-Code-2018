#include <fstream>
#include <climits>
#include <set>

using namespace std;

ifstream fin ("d23.in");
ofstream fout("d23.out");

const long long LGVCHR=201,NBOT=1001;
char chr,vchr[LGVCHR+2];
const long long MAXCOORD=LLONG_MAX;
long long xmin=MAXCOORD,ymin=MAXCOORD,zmin=MAXCOORD;
long long xmax=-MAXCOORD,ymax=-MAXCOORD,zmax=-MAXCOORD;
long long nbot,x,y,z,r,ibot,side,sidenew,igrow,jgrow,kgrow;
long long iterations;

struct sctpoint
{
    long long x,y,z;
};
sctpoint ORIGIN={0,0,0};

struct sctcube
{
    sctpoint bottomleft;
    long long side;
    long long ncovered;
    long long dorigin;
}cube,cubenew,cubetest;

struct cmprule
{
    bool operator()(const sctcube& cube1, const sctcube& cube2) const
    {
        if (cube1.ncovered==cube2.ncovered)
        {
            if (cube1.dorigin==cube2.dorigin)
            {
                return cube1.side<cube2.side;
            }
            return cube1.dorigin<cube2.dorigin;
        }
        return cube1.ncovered>cube2.ncovered;
    }
};

struct sctbot
{
    long long x,y,z,r;
}vbot[NBOT+2];

set <sctcube,cmprule> setcube;
set <sctcube,cmprule>::iterator itcube;

void af()
{
    for (itcube=setcube.begin();itcube!=setcube.end();++itcube)
    {
        cubetest=*itcube;
        fout << cubetest.ncovered << ' ';
    }
    fout << '\n';

}


long long fdcoord (long long coord,long long coord1,long long coord2)
{
    if ( coord < coord1 ) return coord1-coord;
    if ( coord > coord2 ) return coord-coord2;
    return 0;
}

long long fdist (sctpoint point1,sctpoint point2)
{
    return abs(point1.x-point2.x)+abs(point1.y-point2.y)+abs(point1.z-point2.z);
}

void countbots( sctcube &cube3 )
{

    long long x1=cube3.bottomleft.x;
    long long x2=cube3.bottomleft.x+cube3.side-1;

    long long y1=cube3.bottomleft.y;
    long long y2=cube3.bottomleft.y+cube3.side-1;

    long long z1=cube3.bottomleft.z;
    long long z2=cube3.bottomleft.z+cube3.side-1;

    for (long long ibot=0;ibot<nbot;++ibot)
    {
        long long dcubebot=0;
        sctbot bot=vbot[ibot];
        dcubebot+=fdcoord(bot.x,x1,x2);
        dcubebot+=fdcoord(bot.y,y1,y2);
        dcubebot+=fdcoord(bot.z,z1,z2);
        if (dcubebot <= bot.r )
        {
            ++cube3.ncovered;
        }
    }
}

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
        vbot[nbot++].r=r;
    }

    for (ibot=0;ibot<nbot;++ibot)
    {
        if ( vbot[ibot].x - vbot[ibot].r < xmin ) xmin = vbot[ibot].x - vbot[ibot].r;
        if ( vbot[ibot].y - vbot[ibot].r < ymin ) ymin = vbot[ibot].y - vbot[ibot].r;
        if ( vbot[ibot].z - vbot[ibot].r < zmin ) zmin = vbot[ibot].z - vbot[ibot].r;
        if ( vbot[ibot].x - vbot[ibot].r > xmax ) xmax = vbot[ibot].x - vbot[ibot].r;
        if ( vbot[ibot].y - vbot[ibot].r > ymax ) ymax = vbot[ibot].y - vbot[ibot].r;
        if ( vbot[ibot].z - vbot[ibot].r > zmax ) zmax = vbot[ibot].z - vbot[ibot].r;
    }
    cube.bottomleft.x=xmin;
    cube.bottomleft.y=ymin;
    cube.bottomleft.z=zmin;
    cube.dorigin=abs(cube.bottomleft.x) + abs(cube.bottomleft.y) + abs(cube.bottomleft.z);
    side=1;
    while (cube.bottomleft.x + side < xmax || cube.bottomleft.y + side < ymax && cube.bottomleft.z + side < zmax)
    {
        side*=2;
    }
    cube.side=side;
    countbots(cube);
    setcube.insert(cube);

    while (!setcube.empty())
    {
        ++iterations;
        cube=*setcube.begin();
        setcube.erase(setcube.begin());

        side=cube.side;
        if (cube.side==1)
        {
            //af();
            fout << cube.dorigin;
            return 0;
        }
        sidenew=cube.side/2;

        igrow=1;
        x=cube.bottomleft.x;
        while (igrow<=2)
        {
            jgrow=1;
            y=cube.bottomleft.y;
            while (jgrow<=2)
            {
                kgrow=1;
                z=cube.bottomleft.z;
                while (kgrow<=2)
                {
                    cubenew.bottomleft.x=x;
                    cubenew.bottomleft.y=y;
                    cubenew.bottomleft.z=z;
                    cubenew.side=sidenew;
                    cubenew.dorigin=fdist(cubenew.bottomleft,ORIGIN);
                    cubenew.ncovered=0;

                    countbots(cubenew);

                    if (cubenew.ncovered)
                    {
                        setcube.insert(cubenew);
                    }
                    ++kgrow;
                    z+=sidenew;
                }

                ++jgrow;
                y+=sidenew;
            }

            ++igrow;
            x+=sidenew;
        }

    }

    return 0;
}


