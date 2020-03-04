#include<bits/stdc++.h>
const double eps=1e-7;
#define LL long long int
using namespace std;
const int N=1e6+5;
double dp[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        memset(dp,0,sizeof(dp));
        dp[1]=1;
        for(int i=2;i<=n;i++)
        {
            dp[i]=dp[i-1]+1.0*n/(i-1);
        }
        printf("%.5lf\n",dp[n]);
    }
    return 0;
}
