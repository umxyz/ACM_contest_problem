#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
ll gcd(ll a,ll b){return (!b)?a:gcd(b,a%b);}
const int N=500050;
int a[N],sum[N],al[N],ar[N],v[N];
ll ans=0;
void merge(int l,int r)
{
	if(l==r) return ;
	int mid=l+r>>1;
	merge(l,mid);merge(mid+1,r);
	int i=l,j=mid+1,k=l;
	while(i<=mid&&j<=r)
		if(sum[i]>sum[j]) {v[k]=sum[j];ans+=(mid-i+1);k++;j++;}
		else {v[k]=sum[i];i++;k++;}
	while(i<=mid) {v[k]=sum[i];k++;i++;}
	while(j<=r) {v[k]=sum[j];k++;j++;}
	for(int o=l;o<=r;++o) sum[o]=v[o];
}
int main()
{
	freopen("sequence.in","r",stdin);freopen("sequence.out","w",stdout);
	int i,j,k,m,n,l,r;
	scanf("%d%d%d",&n,&l,&r);
	ll all=(ll)n*(ll)(n+1)/2ll;
	for(i=1;i<=n;++i) scanf("%d",&a[i]),al[i]=a[i]-l,ar[i]=a[i]-r;
	for(i=1;i<=n;++i) sum[i]=sum[i-1]+al[i];
	merge(0,n);
	memset(sum,0,sizeof(sum));
	for(i=1;i<=n;++i) sum[i]=sum[i-1]+ar[i];
	reverse(sum,sum+1+n);
	merge(0,n);
	ans=all-ans;
	if(!ans) {printf("0\n");return 0;}
	ll d=gcd(all,ans);
	all/=d;ans/=d;
	if(all==1) printf("%lld\n",ans);
	else printf("%lld/%lld\n",ans,all);
}
