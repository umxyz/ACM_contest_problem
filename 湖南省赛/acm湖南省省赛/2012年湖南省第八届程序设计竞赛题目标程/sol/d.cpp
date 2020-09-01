// Yiming Li
#include<cstdio>
#include<cstring>
#include<cassert>
using namespace std;

char s[1000];
int a[1000];
int rem[1000];
int b[1000];

int main()
{
  int i,j,n,l,t,b1;
  scanf("%d",&t);
  assert(t<=100);
  for (l=0;l<t;l++)
  {
    scanf("%d%s",&n,s);
    assert(2<=n && n<=1000000 && strlen(s)<=20);
    memset(a,0,sizeof(a));
    for (i=19;i>=0;i--)
      if (n>=(1<<i))
      {
        n-=(1<<i);
        a[i+280]=1;
      }
    memcpy(rem,a,sizeof(a));
    for (i=149;i>=0;i--)
    {
      b1=0;
      for (j=299;j>149+i+1;j--)
        if (rem[j]==1)
        {
          b1=1;break;
        }
      if (b1==0)
      {
        for (j=149;j>i;j--)
        {
          if (rem[j+i+1]>b[j])
          {
            b1=1;break;
          }
          if (rem[j+i+1]<b[j])
          {
            b1=-1;break;
          }
        }
      }
      if ((b1==-1)||((b1==0)&&(rem[i+i]==0)&&(rem[i+i+1]==0)))
      {
        b[i]=0;
      }
      else
      {
        b[i]=1;
        for (j=149;j>i;j--)
          rem[j+i+1]-=b[j];
        rem[i+i]--;
        for (j=i+i;j<300;j++)
          if (rem[j]<0)
          {
            rem[j]+=2;
            rem[j+1]--;
          }
      }
    }

    n=strlen(s);
    for (i=139;i>=0;i--)
    {
      b1=1;
      for (j=0;j<n;j++)
        if (b[i-j]!=s[j]-'0') b1=0;
      if (b1==1)
      {
        assert(139-i<=100);
        printf("%d\n",139-i);
        break;
      }
    }
  }
  return 0;
}
