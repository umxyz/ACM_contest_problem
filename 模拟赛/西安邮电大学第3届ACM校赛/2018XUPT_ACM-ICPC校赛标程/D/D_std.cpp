#include<bits/stdc++.h>
using namespace std;
#define  LL long long int
int main()
{
	int T,a,b,n;
	scanf("%d",&T);
	int f[100];
	for(int i=1;i<=T;i++)
	{
		scanf("%d %d %d",&a,&b,&n);
		if(a<b)
		{
			a=a+b;
			b=a-b;
			a=a-b;
		}
		n--;
		LL c=(LL)n*(b+1);
		if(a<=c)
		f[i]=1;
		else
		f[i]=0;
	}
	for(int i=1;i<=T;i++)
	if(f[i]) printf("Yes\n");
	else printf("No\n");
    return 0;
}
