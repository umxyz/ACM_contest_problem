#pragma warning(disable:4786)
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<functional>
#include<string>
#include<cstring>
#include<cstdlib>
#include<queue>
#include<utility>
#include<fstream>
#include<sstream>
#include<cmath>
#include<stack>
#include<assert.h>
using namespace std;

#define MEM(a, b) memset(a, (b), sizeof(a))
#define CLR(a) memset(a, 0, sizeof(a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(X) ( (X) > 0 ? (X) : ( -(X) ) )
#define S(X) ( (X) * (X) )
#define SZ(V) (int )V.size()
#define FORN(i, n) for(i = 0; i < n; i++)
#define FORAB(i, a, b) for(i = a; i <= b; i++)
#define ALL(V) V.begin(), V.end()

typedef pair<int,int> PII;
typedef pair<double, double> PDD;
typedef vector<int> VI;

#define IN(A, B, C) assert( B <= A && A <= C)

//typedef int LL;
//typedef __int64 LL;

int a[100005], b[100005], h[100005];

int main()
{
	int n, m, K;
	int i, j, k;
	int ans, now;
	int ks = 0;

	while(scanf("%d %d %d", &n, &m, &K)!=EOF)
	{
		IN(n, 1, 100000);
		IN(m, 1, 100000);
		IN(K, 1, 100000);

		for(i = 0; i < n; i++) 
		{
			scanf("%d", &h[i]);
			IN(h[i], 2, 100000000);
		}

		for(i = 0; i < m; i++)
		{
			scanf("%d %d", &a[i], &b[i]);

			if(i) assert(a[i] > b[i - 1]);
			assert(a[i] > b[i]);
			IN(a[i], 1, 100000000);
			IN(b[i], 1, 100000000);
		}

		b[m - 1] = 1;

		sort(h, h + n);
		sort(a, a + m);
		sort(b, b + m);

		ans = j = k = 0;
		for(i = 0; i < n; i++)
		{
			while(j < m && a[j] < h[i]) j++;
			while(k < m && b[k] < h[i]) k++;

			now = k - j;

			if(now >= K) ans++;
		}

		printf("Case %d: %d\n", ++ks, ans);
	}

	return 0;
}
