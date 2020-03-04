#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
using namespace std;  
#define LL long long int
const int N=1e5+5;
int sum[N];
int f[N];
int ans[15];
int main()
{  
    int T;
    scanf("%d",&T);
    int n,m;
    for(int j=1;j<=T;j++)
    {
        int flag=0;
        scanf("%d%d",&n,&m);
        sum[0]=0;
        memset(f,0,sizeof f);
        for(int i=1;i<=n;i++)
        {
            int x;
            scanf("%d",&x);
            sum[i]=sum[i-1]+x;
            int wei=sum[i]%m;
            f[wei]++;
            if(f[wei]%2==0) flag=1;
        }
        if(flag==1||f[0])
            ans[j]=1;//printf("YES\n");
        else 
            ans[j]=0;//printf("NO\n");
    }
    for(int i=1;i<=T;i++)
    if(ans[i]) printf("Yes\n");
    else printf("No\n");
    return 0;
}