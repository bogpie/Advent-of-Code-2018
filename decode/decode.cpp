#include <fstream>

using namespace std;

ifstream fin ("decode.in");
ofstream fout("decode.out");

char ch;
int n;

int main()
{
    while (fin>>ch)
    {
        fin >> n;
        n-=127877;
        ch=n;

        fout<<ch;
    }
}
