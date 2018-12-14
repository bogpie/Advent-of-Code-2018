#include <fstream>
#include <vector>

using namespace std;

ifstream fin ("p14.in");
ofstream fout("p14.out");

const int NELF=2;
vector <int> v;
int n,sum,ncrt,i,vpoz[NELF+2];

int main()
{
    fin >> n;

    v.push_back(3);
    v.push_back(7);

    //ncrt=2;
    vpoz[0]=0;
    vpoz[1]=1;

    while (v.size()<=n+12)
    {
        sum=v[vpoz[0]]+v[vpoz[1]];
        if (sum/10)
        {
            v.push_back(sum/10);
        }
        v.push_back(sum%10);
        ncrt=v.size();
        vpoz[0]=(vpoz[0]+v[vpoz[0]]+1)%ncrt;
        vpoz[1]=(vpoz[1]+v[vpoz[1]]+1)%ncrt;
    }

    for (i=n;i<=n+9;++i)
    {
        fout << v[i];
    }

    return 0;
}
