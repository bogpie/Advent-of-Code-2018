<<<<<<< HEAD
#include <iostream>

using namespace std;

int winnerteam,st,dr,mid;

int main()
{
    st=1;
    dr=100;

    while (st<dr)
    {
        mid=(st+dr)/2;

        cout << " Manually boost by " << mid << "\n";
        cout << " Which team wins (1 for Immune System, 2 for Infection or for Tie) ";
        cin >> winnerteam;
        if (winnerteam==1)
        {
            dr=mid;
        }
        else
        {
            st=mid+1;
        }
    }

    cout << st;

    return 0;
}
=======
#include <iostream>

using namespace std;

int winnerteam,st,dr,mid;

int main()
{
    st=1;
    dr=100;

    while (st<dr)
    {
        mid=(st+dr)/2;

        cout << " Manually boost by " << mid << "\n";
        cout << " Which team wins (1 for Immune System, 2 for Infection or for Tie) ";
        cin >> winnerteam;
        if (winnerteam==1)
        {
            dr=mid;
        }
        else
        {
            st=mid+1;
        }
    }

    cout << st;

    return 0;
}
>>>>>>> c1c510468a99df7674dc42d4a9ed67c9c4bd8549
