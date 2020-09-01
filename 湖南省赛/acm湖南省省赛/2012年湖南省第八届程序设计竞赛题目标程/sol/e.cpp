// Yiming Li
#include<cstdio>
#include<cstring> 
#include<vector>
#include<string>
#include<algorithm>
#include<cassert>
using namespace std;

vector<string> a;
char s[1010000];
int d[2000];

int main()
{
  int i,j,l,t,n,ans;
  scanf("%d",&t);
  assert(t<=10);
  for (l=0;l<t;l++)
  {
    scanf("%d",&n);
    assert(1<=n&&n<=1000);
    a.clear();
    int tot = 0;
    for (i=0;i<n;i++)
    {
      scanf("%s",s);
      tot += strlen(s);
      a.push_back(s);
    }
    assert(tot <= 1000000);
    sort(a.begin(),a.end());
    memset(d,0,sizeof(d));
    for (i=0;i+1<n;i++)
    {
      for (j=0;j<a[i].length()&&j<a[i+1].length();j++)
        if (a[i][j]!=a[i+1][j]) break;
      if (j+1>d[i]) d[i]=j+1;
      if (j+1>d[i+1]) d[i+1]=j+1;
    }
    ans=0;
    for (i=0;i<n;i++)
      ans+=d[i];
    printf("%d\n",ans);
  }
  return 0;
}
