#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

inline int read(){int ra,fh;char rx;rx=getchar(),ra=0,fh=1;
while((rx<'0'||rx>'9')&&rx!='-')rx=getchar();if(rx=='-')
fh=-1,rx=getchar();while(rx>='0'&&rx<='9')ra*=10,ra+=rx-48,
rx=getchar();return ra*fh;}

const int INF = 1e9;

string s;
int main()
{
//    freopen("data.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    int n;
    int a;
    int hour;
    int mini;
    cin >> s;
    hour = ((int)(s[0]-'0'))*10+((int)(s[1]-'0'));
    mini = ((int)(s[3]-'0'))*10+((int)(s[4]-'0'));
    cin >> n;
    for(int i=0;i<n-1;i++)
    {
        cin >> a;
        mini += a;
        hour += mini/60;
        mini %= 60;
        hour %= 24;
        if(hour<10)
        {
            cout <<"0";
        }
        cout << hour<<":";
        if(mini<10)
        {
            cout <<"0";
        }
        cout << mini<<endl;
    }
    return 0;
}
