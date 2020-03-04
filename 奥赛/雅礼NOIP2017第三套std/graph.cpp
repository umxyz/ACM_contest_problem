#include<cstdio>
using namespace std;
const int mod=1000000007;
int dp[35][35][550][10],n,m,kk,i,j,l,k;
int main()
{
	freopen("graph.in","r",stdin);freopen("graph.out","w",stdout);
    scanf("%d%d%d",&n,&m,&kk);
    dp[1][0][0][0]=1;
    for(i=1;i<=n;++i) for(j=0;j<=m;++j) for(k=0;k<(1<<kk+1);++k)
    {
        for(l=0;l<kk;++l)
        {
            (dp[i][j][k][l+1]+=dp[i][j][k][l])%=mod;
            if(j<m&&i-kk+l>0) (dp[i][j+1][k^(1<<kk)^(1<<l)][l]+=dp[i][j][k][l])%=mod;
        }
        if(!(k&1)) (dp[i+1][j][k>>1][0]+=dp[i][j][k][kk])%=mod;
    }
    printf("%d",dp[n+1][m][0][0]);
    return 0;
}
