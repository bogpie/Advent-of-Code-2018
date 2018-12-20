#include <fstream>
#include <cstring>

using namespace std;

ifstream fin ("d20.in");
ofstream fout("d20.out");

const int NCHR=14230;
int ichr,length,nchr,sol,istack;
int vstack[NCHR+10];
int voldstack[NCHR+10];
char vchr[NCHR+2];

bool iscoord (char chr)
{
    if (chr=='N' || chr=='E' || chr=='W' || chr=='S')
    {
        return 1;
    }
    return 0;
}

int main()
{
    fin.getline(vchr,NCHR);
    vchr[0]='(';
    nchr=strlen(vchr);
    vchr[nchr-1]=')';

    ++istack;
    ichr=1;

    while (istack)
    {

        while (iscoord(vchr[ichr]))
        {
            ++vstack[istack];
            ++ichr;
        }

        if (vchr[ichr]=='|')
        {
            if (vchr[ichr+1]==')')
            {
                --istack;
                ichr+=2;
            }
            else
            {
                voldstack[istack]=vstack[istack];
                vstack[istack]=vstack[istack-1];
                ++ichr;
            }
        }
        else if (vchr[ichr]=='(')
        {
            vstack[istack+1]=vstack[istack];
            ++istack;
            ++ichr;
        }
        else
        {
            vstack[istack-1]=max(vstack[istack],voldstack[istack]);
            --istack;
            ++ichr;
        }
    }

    fout << " part 1 : " << vstack[1] << '\n';

    return 0;
}
