#include <fstream>

using namespace std;

ifstream fin ("d25.in");
ofstream fout("d25.out");

const int NPOINT=1479;
int ipoint,jpoint,npoint,ngroup,iroot,jroot;
int vgroup[NPOINT+2],vparent[NPOINT+2],vheight[NPOINT+2];
char chr;
bool foundgroup;
bool isroot[NPOINT+2];

struct sctpoint
{
    int x,y,z,t;
}vpoint[NPOINT+2];

int manhattan (sctpoint a,sctpoint b)
{
    return (abs(a.x-b.x))+(abs(a.y-b.y))+(abs(a.z-b.z))+(abs(a.t-b.t));
}

int froot(int ipoint)
{
    int irad,iparent;

    irad=ipoint;
    while (vparent[irad]!=irad)
    {
        irad=vparent[irad];
    }

    while (vparent[ipoint]!=ipoint)
    {
        iparent=vparent[ipoint];
        vparent[ipoint]=irad;

        ipoint=iparent;
    }

    return irad;
}

void fmerge (int ipoint,int jpoint)
{
    if (vheight[ipoint]>vheight[jpoint])
    {
        vparent[jpoint]=ipoint;
    }
    else
    {
        vparent[ipoint]=jpoint;
    }

    if (vheight[ipoint]==vheight[jpoint])
    {
        ++vheight[jpoint];
    }
}

int main()
{
    while (fin>>vpoint[++ipoint].x)
    {
        fin >> chr >> vpoint[ipoint].y >> chr >> vpoint[ipoint].z >> chr >> vpoint[ipoint].t ;
    }
    npoint=ipoint-1;
    for (ipoint=1;ipoint<=npoint;++ipoint)
    {
        vparent[ipoint]=ipoint;
        vheight[ipoint]=1;
    }
    for (ipoint=1;ipoint<=npoint;++ipoint)
    {
        for (jpoint=2;jpoint<=npoint;++jpoint)
        {
            iroot=froot(ipoint);
            jroot=froot(jpoint);
            if ( iroot==jroot )
            {
                continue;
            }
            if (manhattan(vpoint[ipoint],vpoint[jpoint])<=3)
            {
                fmerge(iroot,jroot);
            }
        }
    }

    for (ipoint=1;ipoint<=npoint;++ipoint)
    {
        iroot=froot(ipoint);
        isroot[iroot]=1;
    }
    for (ipoint=1;ipoint<=npoint;++ipoint)
    {
        if (isroot[ipoint])
        {
            ++ngroup;
        }
    }

    fout << " part one : " << ngroup << "\n";

    return 0;
}
