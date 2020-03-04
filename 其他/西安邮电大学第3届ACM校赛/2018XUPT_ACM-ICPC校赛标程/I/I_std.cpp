#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn=1e3+10;

int a[maxn],b[maxn];

int main()
{
    int n,a1,b1,a2,b2,ans;
    //freopen("11.in","r",stdin);
    //freopen("11.out","w",stdout);
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    for(int i=0;i<n;i++)
        scanf("%d",&b[i]);
    sort(a,a+n);
    sort(b,b+n);
    a1=b1=0;
    a2=b2=n-1;
    ans=0;
    while(a2>=a1)
    {
        if(a[a2]>b[b2])
        {
            a2--;
            b2--;
            ans++;
        }
        else if(a[a2]<b[b2])
        {
            a1++;
            b2--;
            ans--;
        }
        else
        {
            if(a[a1]>b[b1])
            {
                a1++;
                b1++;
                ans++;
            }
            else
            {
                if(a[a1]<b[b2])
                    ans--;
                a1++;
                b2--;
            }
        }
    }
    printf("%d\n",ans*200);
    return 0;
}
