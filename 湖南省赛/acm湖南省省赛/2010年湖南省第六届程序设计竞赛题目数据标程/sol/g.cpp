#include<cstdio>
#include<cmath>
#include<vector>
using namespace std;

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b)  ((a) < (b) ? (a) : (b))
#define inf 1000000000

double d[205][205];
double v[205][205],u[205][205];

int main()
{
	int i,j,k,tests,cs=0,n,m;
	while(scanf("%d%d",&n,&m)==2)
	{
		if(!n && !m) break;

		for(i=1;i<=n;i++)
				for(j=1;j<=n;j++)
					d[i][j]=d[j][i]=v[i][j]=v[j][i]=inf;


		for(i=0;i<m;i++)
		{
			int a,b;
			double vv,tt;
			scanf("%d%d%lf%lf",&a,&b,&vv,&tt);
			d[a][b]=d[b][a]=vv;
			v[a][b]=v[b][a]=vv;
			u[a][b]=u[b][a]=tt;
		}


		for(k=1;k<=n;k++)
			for(i=1;i<=n;i++)
				for(j=1;j<=n;j++)
					d[i][j]=MIN(d[i][j],d[i][k]+d[k][j]);

		for(i=1;i<=n;i++)
			d[i][i]=0.0;

		double ans=d[1][n];

		if(ans==inf)
		{
			puts("-1.000");
			continue;
		}

		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
			{
				if(i==j || v[i][j]==inf) continue;

				double lo=0.0,hi=10.0;
				double t1=d[1][i];

				while(hi-lo>1e-6)
				{
					double left  = (2.0*lo+hi)/3.0;
					double right = (lo+2.0*hi)/3.0;

					double l1= t1+left  + v[i][j]*pow(u[i][j],-t1-left)  + d[j][n];
					double l2= t1+right + v[i][j]*pow(u[i][j],-t1-right) + d[j][n];

					if(l1<l2)
						hi=right;
					else
						lo=left;

					ans=MIN(ans,MIN(l1,l2));
				}
			}

		printf("%.3lf\n",ans);
	}
	return 0;
}
