#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long ll;

const int maxn=1e2+10;
const int maxm=1e4+10;

ll sv[maxn][maxm],sl[maxn][maxm],dp[maxn][maxm];
int q[maxm];

int main()
{
    int n,m,k;
    //freopen("3.in","r",stdin);
    //freopen("3.out","w",stdout);
    scanf("%d %d %d",&n,&m,&k);
    int t;
    for(int i=1;i<=n+1;i++)
    {
        sv[i][0]=0;
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&t);
            sv[i][j]=sv[i][j-1]+t;
        }
    }
    for(int i=1;i<=n+1;i++)
    {
        sl[i][0]=0;
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&t);
            sl[i][j]=sl[i][j-1]+t;
        }
    }
    int front,rear;
    for(int j=0;j<=m;j++)
        dp[0][j]=0;
    for(int i=1;i<=n+1;i++)
    {
        front=0;rear=-1;
        for(int j=0;j<=m;j++)
        {
            while(front<=rear&&dp[i-1][q[rear]]-sv[i][q[rear]]<=dp[i-1][j]-sv[i][j])
                rear--;
            q[++rear]=j;
            while(sl[i][j]-sl[i][q[front]]>k)
                front++;
            dp[i][j]=sv[i][j]+dp[i-1][q[front]]-sv[i][q[front]];
        }
        front=0;rear=-1;
        for(int j=m;j>=0;j--)
        {
            while(front<=rear&&dp[i-1][q[rear]]+sv[i][q[rear]]<=dp[i-1][j]+sv[i][j])
                rear--;
            q[++rear]=j;
            while(sl[i][q[front]]-sl[i][j]>k)
                front++;
            dp[i][j]=max(dp[i][j],-sv[i][j]+dp[i-1][q[front]]+sv[i][q[front]]);
        }
    }
    ll ans=0;
    for(int j=0;j<=m;j++)
        ans=max(ans,dp[n+1][j]);
    printf("%lld\n",ans);
    return 0;
}
