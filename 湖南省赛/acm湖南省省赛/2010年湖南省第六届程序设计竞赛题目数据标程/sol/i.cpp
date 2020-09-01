#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod=987654321;

ll A[2][2],B[2][2],T[2][2];

void pow(int n)
{
	if(n==0)
	{
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				B[i][j]=(i==j);
		return;
	}
	if(n&1)
	{
		pow(n-1);
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
			{
				T[i][j]=0;
					for(int k=0;k<2;k++)
						T[i][j]=(T[i][j]+A[i][k]*B[k][j])%mod;
			}
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
			{
				B[i][j]=T[i][j];
			}
		
	}
	else
	{
		pow(n/2);
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
			{
				T[i][j]=0;
					for(int k=0;k<2;k++)
						T[i][j]=(T[i][j]+B[i][k]*B[k][j])%mod;
			}
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
			{
				B[i][j]=T[i][j];
			}
		
	}
}

int main()
{
  int n;
  A[0][0]=1;	A[0][1]=1;
  A[1][0]=1;	A[1][1]=0;
  while (scanf("%d", &n) == 1 && n)
  {
	ll ans=0;
	if(n&1) ans=0;
	else if(n<4) ans=0;
	else
	{
		pow(n-4);
		ans=B[0][0]-n/2+1;
		ans%=mod;
		if(ans<0)ans+=mod;
	}
	printf("%lld\n",ans);
  }

  return 0;
}
