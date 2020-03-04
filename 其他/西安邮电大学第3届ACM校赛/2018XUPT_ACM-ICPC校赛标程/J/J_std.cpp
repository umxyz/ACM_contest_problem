#include<cstdio>

typedef long long ll;

const int MOD=1e9;
const int maxn=1e3+10;

int f[maxn][maxn];

int main()
{
    int n,sum;
    //freopen("14.in","r",stdin);
    //freopen("14.out","w",stdout);
    for(int i=1;i<maxn;i++)
        f[i][i]=0;
    f[1][0]=1;
    for(int i=2;i<maxn;i++)
    {
        sum=0;
        for(int j=0;j<i;j++)
        {
            sum=(sum+f[i-1][j])%MOD;
            f[i][j]=sum;
        }
    }
    scanf("%d",&n);
    printf("%d\n",f[n+1][n]);
    return 0;
}
