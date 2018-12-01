#include <fstream>

using namespace std;

ifstream fin ("1.in");
ofstream fout("1.out");

long long sum,x;

int main()
{
    while (fin>>x)
    {
        sum+=x;
    }

    fout << sum ;

    return 0;
}
