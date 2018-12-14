#include <fstream>
#include <vector>

using namespace std;

ifstream fin ("8.in");
ofstream fout("8.out");

const int NCH=8888,NMET=21;
int aux;
int totmet,inod,nnod,imet,met;
int fr[NCH][NCH];
int vch[NCH][NCH],vmet[NCH][NMET];
int szch[NCH],szmet[NCH];


int fvalue (int inod)
{
    int nch=szch[inod];
    if (!nch)
    {
        int metleaf=0;
        int nmet=szmet[inod];
        for (int imet=1;imet<=nmet;++imet)
        {
            metleaf+=vmet[inod][imet];
        }
        return metleaf;
    }

    int valcrt=0;

    for (int ich=1;ich<=nch;++ich)
    {
        valcrt += fr[inod][ich] * fvalue(vch[inod][ich]);
    }

    return valcrt;
}

void parse (int inod)
{
    int nch=0;
    int nmet=0;

    fin >> nch >> nmet;

    if (inod==NCH-1)
    {
        ++aux;
    }

    for (int ich=1;ich<=nch;++ich)
    {
        ++nnod;
        vch[inod][++szch[inod]]=nnod;
        parse(nnod);
    }

    for (int imet=1;imet<=nmet;++imet)
    {
        int met=0;
        fin >> met;
        vmet[inod][++szmet[inod]]=met;
        totmet+=met;
    }

}

int main()
{
    nnod=inod=1;
    parse(inod);
    fout << totmet << '\n';

    for (inod=1;inod<=nnod;++inod)
    {
        for (imet=1;imet<=szmet[inod];++imet)
        {
            met=vmet[inod][imet];
            ++fr[inod][met];
        }
    }

    fout << fvalue(1);

    return 0;
}
