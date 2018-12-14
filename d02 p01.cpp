#include <fstream>
#include <cstring>

using namespace std;

ifstream fin ("2a.in");
ofstream fout("2a.out");

unsigned long long lg,sol,sol2,sol3,i,nlitrep;
unsigned long long ap[26],vsol[4];
char id[1111];

int main()
{
    while (fin>>id)
    {
        lg=strlen(id);

        for (i=0;i<=25;++i)
        {
            ap[i]=0;
        }

        for (i=0;i<lg;++i)
        {
            ++ap[id[i]-'a'];
        }

        for (nlitrep=2;nlitrep<=3;++nlitrep)
        {
            for (i=0;i<=25;++i)
            {
                if (ap[i]==nlitrep)
                {
                    ++vsol[nlitrep];
                    break;
                }
            }
        }
    }

    sol=vsol[2]*vsol[3];

    fout << sol;

    return 0;
}
