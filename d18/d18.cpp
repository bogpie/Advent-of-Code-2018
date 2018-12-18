#include <fstream>
#include <cstring>

using namespace std;

ifstream fin ("d18.in");
ofstream fout("d18.out");

const long long NCOORD=50,NTIME=10;
long long itime,ilin,icol,imat,tot,imatold,totold,vtot[9999];
long long printtime=512;
char mat[3][NCOORD+5][NCOORD+5];
long long dlin[]={ 0,-1,-1, 0,+1,+1,+1, 0,-1};
long long dcol[]={ 0, 0,+1,+1,+1, 0,-1,-1,-1};

void af(long long imat,long long imatold,long long itime)
{
    fout << "After " << itime << " min \n";

    fout <<"current matrix :\n";

    long long offset;
    offset=0;
    for (long long ilin=1-offset;ilin<=NCOORD+offset;++ilin)
    {
        for (long long icol=1-offset;icol<=NCOORD+offset;++icol)
        {
            fout << mat[imat][ilin][icol];
        }
        fout <<'\n';
    }
    fout <<'\n';

    fout <<"old matrix :\n";

    offset=0;
    for (long long ilin=1-offset;ilin<=NCOORD+offset;++ilin)
    {
        for (long long icol=1-offset;icol<=NCOORD+offset;++icol)
        {
            fout << mat[imatold][ilin][icol];
        }
        fout <<'\n';
    }
    fout <<'\n';
}

void fcount(long long imat,long long &tot)
{
    long long ntree=0,nlumb=0;
    tot=0;
    for (long long ilin=1;ilin<=NCOORD;++ilin)
    {
        for (long long icol=1;icol<=NCOORD;++icol)
        {
            char chr=mat[imat][ilin][icol];
            if (chr=='|')
            {
                ++ntree;
            }
            else if (chr=='#')
            {
                ++nlumb;
            }
        }
    }
    tot=ntree*nlumb;
}

void fturn(long long imat,long long imatold,long long ilin,long long icol,char chrif,char chrelse,long long ntreeneed,long long nlumbneed)
{
    long long ntree=0,nlumb=0;
    if (itime==2 && ilin==10 && icol==2)
    {
        long long aux=1;
    }
    for (long long idir=1;idir<=8;++idir)
    {
        long long ilinad=ilin+dlin[idir];
        long long icolad=icol+dcol[idir];
        char chrad=mat[imatold][ilinad][icolad];
        if (chrad=='|')
        {
            ++ntree;
        }
        else if (chrad=='#')
        {
            ++nlumb;
        }
    }
    if (ntree>=ntreeneed && nlumb>=nlumbneed)
    {
        mat[imat][ilin][icol]=chrif;
    }
    else
    {
        mat[imat][ilin][icol]=chrelse;
    }
}

void fselect (long long imat,long long imatold,long long ilin, long long icol)
{
    char chr=mat[imatold][ilin][icol];

    if (chr=='.')
    {
        fturn(imat,imatold,ilin,icol,'|','.',3,0);
    }
    else if (chr=='|')
    {
        fturn(imat,imatold,ilin,icol,'#','|',0,3);
    }
    else
    {
        fturn(imat,imatold,ilin,icol,'#','.',1,1);
    }
}

void fbord()
{
    for (long long imat=0; imat<=1; ++imat)
    {
        for (long long icoord=0; icoord<=NCOORD+1; ++icoord)
        {
            mat[imat][icoord][0]=mat[imat][icoord][NCOORD+1]=mat[imat][0][icoord]=mat[imat][NCOORD+1][icoord]='x';
        }
    }
}

void fcopy(long long imat1,long long imat2)
{
    for (long long ilin=1;ilin<=NCOORD;++ilin)
    {
        strcpy(mat[imat2][ilin]+1,mat[imat1][ilin]+1);
    }
}

int main()
{

    while (fin.getline(mat[0][++ilin]+1,51))
    {
        ;
    }
    imat=0;
    imatold=1;
    fbord();
    fcopy(imat,imatold); //af(imat,imatold,itime);
    for (itime=1; itime<=9999; ++itime)
    {
        for (ilin=1; ilin<=NCOORD; ++ilin)
        {
            for (icol=1; icol<=NCOORD; ++icol)
            {
                fselect(imat,imatold,ilin,icol);
            }
        }
        //af(imat,imatold,itime);fcopy(imat,imatold);
        totold=tot;
        fcount(imat,tot);
        vtot[itime]=tot;

        if (itime==10)
        {
            fout << " part one here : ";
        }
        else if (itime==printtime)
        {
            printtime+=28;
            fout <<"pattern start: ";

        }
        fout << itime <<" "<<tot << "  //  " << tot-totold << '\n';
        swap(imat,imatold);

    }

    fout << "part 1 : " << vtot[10] << '\n' ;
    fout << "part 2 : " << vtot[(1000000000-512)%28+512] << '\n' ;

    return 0;
}
