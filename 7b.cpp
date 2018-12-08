#include <fstream>
#include <set>
#include <algorithm>
using namespace std;
ifstream fin ("7.in");
ofstream fout("7.out");
set <int> squ;
set <int>::iterator it;
char sir[100],chx,chy;
int x,i,ntasks,sec,y,ielf;
int mdrum[31][31],ex[31],ntat[31],timp[31],task[31];
bool bson[31];

char chr(int ilit)
{
    return ilit+'A'-1;
}


int main()
{
    while (fin >> sir)
    {
        fin >> chx;
        x=chx-'A'+1;
        for (i=1; i<=5; ++i)
        {
            fin >> sir;
        }
        fin >> chy;
        y=chy-'A'+1;
        for (i=1; i<=2; ++i)
        {
            fin >> sir;
        }
        if (mdrum[x][y]) continue;
        mdrum[x][y]=1;
        ex[x]=ex[y]=1;
        ++ntat[y];
        bson[y]=1;
    }
    for (i=1; i<=26; ++i)
    {
        if (ex[i])
        {
            ++ntasks;
        }
        if (ex[i] && !bson[i])
        {
            squ.insert(i);
        }
    }

    while (ntasks)
    {

        for (ielf=1; ielf<=5; ++ielf) //actualizeaza
        {
            if (!timp[ielf])
            {
                if(task[ielf])
                {
                    if (ex[task[ielf]])
                    {
                        --ntasks;
                    }
                    if(!ntasks)
                    {
                        fout <<sec;
                        return 0;
                    }

                    ex[task[ielf]]=0;
                    x=task[ielf];
                    task[ielf]=0;
                    for (y=1; y<=26; ++y)
                    {
                        if (mdrum[x][y])
                        {
                            if (ntat[y]==1)
                            {
                                squ.insert(y);
                            }
                            --ntat[y];
                        }
                    }
                }
                if(squ.empty()) continue;
                it=squ.begin();
                x=*it;
                task[ielf]=x;
                timp[ielf]=x-1+60;

                squ.erase(squ.begin());



            }
            else if(timp[ielf])
            {
                --timp[ielf];
            }
        }
        ++sec;
    }


    //fout << '\n';

    return 0;
}

