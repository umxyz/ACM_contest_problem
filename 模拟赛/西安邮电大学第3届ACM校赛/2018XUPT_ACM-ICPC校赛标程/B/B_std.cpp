#include<cstdio>
#include<algorithm>
#include<iostream>
#define ll long long
using namespace std;
inline int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}

int n,tot;
ll ans;
struct data{int t,d;}a[100001];
inline bool cmp(data a,data b){return a.t*b.d<a.d*b.t;}
int main()
{

    cin >> n;
    for(int i=1;i<=n;i++)
    {
        cin >> a[i].t >> a[i].d ;
        tot+=a[i].d;
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++)
    {
        tot-=a[i].d;
        ans+=a[i].t*tot;
    }
    cout << ans<<endl;
    return 0;
}
