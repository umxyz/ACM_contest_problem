#include <cstdio> 
#include <cstring> 
using namespace std;

int r,c;
char a[20][20];
int used[20][20];
int ans[100];
int ansl;
int aa[100];
int zhan[100][2];
int used1[20][20];
int neigh[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
int z;

void search(int x,int y,int l)
{
	int i,j,top,bottom,xx,yy;
	if ((l>ansl)||((l==ansl)&&(z==1)))
	{
		memcpy(ans,aa,sizeof(ans));
		ansl=l;
		z=0;
	}
	memset(used1,0,sizeof(used1));
	used1[x][y]=1;
	top=0;bottom=1;
	zhan[0][0]=x;
	zhan[0][1]=y;
	while (top<bottom)
	{
		for (i=0;i<4;i++)
		{
			xx=zhan[top][0]+neigh[i][0];
			yy=zhan[top][1]+neigh[i][1];
			if ((xx>=0)&&(xx<r)&&(yy>=0)&&(yy<c)&&(a[xx][yy]!='#')&&(used[xx][yy]==0)&&(used1[xx][yy]==0))
			{
				zhan[bottom][0]=xx;
				zhan[bottom][1]=yy;
				used1[xx][yy]=1;
				bottom++;
			}
		}
		top++;
	}
	if (l+top-1<ansl) return;
	if ((l+top-1==ansl)&&(z==-1)) return;
	for (i=0;i<4;i++)
	{
		xx=x+neigh[i][0];
		yy=y+neigh[i][1];
		if ((xx>=0)&&(xx<r)&&(yy>=0)&&(yy<c)&&(a[xx][yy]!='#')&&(used[xx][yy]==0))
		{
			aa[l]=a[xx][yy]-'0';
			used[xx][yy]=1;
			if (z!=0)
				search(xx,yy,l+1);
			else
				if (l>=ansl)
				{
					z=1;
					search(xx,yy,l+1);
					z=0;
				}
				else
				{
					if (aa[l]>ans[l])
					{
						z=1;
						search(xx,yy,l+1);
						z=0;
					}
					else if (aa[l]==ans[l])
					{
						z=0;
						search(xx,yy,l+1);
						z=0;
					}
					else
					{
						z=-1;
						search(xx,yy,l+1);
						z=0;
					}
				}
			used[xx][yy]=0;
		}
	}
}

int main()
{
	int i,j;
	while (1)
	{
		scanf("%d%d",&r,&c);
		if ((r==0)&&(c==0)) break;
		for (i=0;i<r;i++)
			scanf("%s",a[i]);
		memset(ans,0,sizeof(ans));
		ans[0]=-1;
		ansl=1;
		memset(aa,0,sizeof(aa));
		for (i=0;i<r;i++)
			for (j=0;j<c;j++)
				if (a[i][j]!='#')
				{
					used[i][j]=1;
					aa[0]=a[i][j]-'0';
					if (a[i][j]-'0'>ans[0])
					{
						z=1;
						search(i,j,1);
					}
					else if (a[i][j]-'0'==ans[0])
					{
						z=0;
						search(i,j,1);
					}
					else
					{
						z=-1;
						search(i,j,1);
					}
					used[i][j]=0;
				}
		for (i=0;i<ansl;i++)
			printf("%d",ans[i]);
		printf("\n");
	}
	return 0;
}

