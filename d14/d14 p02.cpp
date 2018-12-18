#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

ifstream fin ("p14.in");
ofstream fout("p14.out");

const int NELF=2,NMAX=99999999;
char *pt,v[NMAX+2];
int n,sum,ncrt,i,vpoz[NELF+2];

int main()
{
    //fin >> n;

    n=NMAX-14;

    v[ncrt++]='3';
    v[ncrt++]='7';

    //ncrt=2;
    vpoz[0]=0;
    vpoz[1]=1;

    while (ncrt<=n+12)
    {
        sum=v[vpoz[0]]+v[vpoz[1]]-'0'-'0';
        if (sum/10)
        {
            v[ncrt++]=sum/10+'0';
        }
        v[ncrt++]=sum%10+'0';
        vpoz[0]=(vpoz[0]+v[vpoz[0]]-'0'+1)%ncrt;
        vpoz[1]=(vpoz[1]+v[vpoz[1]]-'0'+1)%ncrt;
    }

    //fout << v;
    pt=strstr(v,"236021");
    fout << pt-v;
    return 0;
}
