#include <fstream>

using namespace std;

ifstream fin ("9.in");
ofstream fout("9.out");

const long long NMARB=7117002;
long long isir,nelf,nmarb,poz,ipoz,mx,imarb,ngame,ielf;
long long vgame[NMARB],vscor[420],aux;
char sir[102];

int main()
{
    fin >> nelf;
    for (isir=1;isir<=5;++isir)
    {
        fin >> sir;
    }
    fin >> nmarb;
    fin >> sir;

    vgame[poz=ngame=1]=0;

    for (imarb=1;imarb<=nmarb;++imarb)
    {

        ++ielf;
        if (ielf>nelf)
        {
            ielf=1;
        }

        if (imarb % 23 == 0)
        {
            vscor[ielf]+=imarb;
            poz-=7;
            if (poz<=0)
            {
                poz = ngame+poz;
            }
            vscor[ielf]+=vgame[poz];

            //fout << imarb << ' ' << vgame[poz] << '\n';

            for (ipoz=poz;ipoz<=ngame;++ipoz)
            {
                vgame[ipoz]=vgame[ipoz+1];
            }
            --ngame;
            continue;
        }
        poz=poz+2;
        if (poz>ngame+1)
        {
            poz=poz-ngame;
        }


        for (ipoz=ngame;ipoz>=poz;--ipoz)
        {
            vgame[ipoz+1]=vgame[ipoz];
        }
        ++ngame;
        vgame[poz]=imarb;
    }

    for (ielf=1;ielf<=nelf;++ielf)
    {
        if (vscor[ielf]>mx)
        {
            mx=vscor[ielf];
        }
    }
    fout << mx;
    return 0;
}

