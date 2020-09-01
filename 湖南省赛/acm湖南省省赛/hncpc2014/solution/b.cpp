#include<list>
#include<bitset>
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
#define IN(A, B, C)  ((B) <= (A) && (A) <= (C))

typedef pair<int,int> PII;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector<PII > VP;

#define AIN(A, B, C) assert(IN(A, B, C))

int MOD = 1000000007;
int dp[21][17][1<<17];
int h[20][20], H;
int R, C;

int DP(int _h, int pos, int mask, int flag)
{
	if(pos == R * C) return DP(_h + 1, 0, mask, flag);
	if(_h == H + 1) return mask == 0;
	int &ret = dp[_h][pos][mask];
	if(ret != -1) return ret;
	ret = 0;

	int r = pos / C;
	int c = pos % C;

	if(mask & (1 << pos)) return ret = DP(_h, pos + 1, mask ^ (1 << pos), flag);
	if(h[r][c] < _h) return ret = DP(_h, pos + 1, mask, flag);
	if(c + 1 < C && (mask & (1 << (pos + 1))) == 0 && h[r][c + 1] >= _h)
		ret = (ret + DP(_h, pos + 1, mask | (1 << (pos + 1)), flag)) % MOD;
	if(r + 1 < R && (mask & (1 << (pos + C))) == 0 && h[r + 1][c] >= _h)
		ret = (ret + DP(_h, pos + 1, mask | (1 << (pos + C)), flag)) % MOD;
	if(_h + 1 <= h[r][c])
		ret = (ret + DP(_h, pos + 1, mask | (1 << pos), flag)) % MOD;
	if(flag)
		ret = (ret + DP(_h, pos + 1, mask, flag)) % MOD;

	return ret;
}

int main()
{
	int ks = 0;
	int i, j;
	while(scanf("%d %d", &R, &C) != EOF)
	{
		AIN(R * C, 1, 16);
		H = 0;
		FORN(i, R) FORN(j, C) 
		{
			scanf("%d", &h[i][j]); 
			AIN(h[i][j], 0, 20);
			H = MAX(H, h[i][j]);
		}
		MEM(dp, -1);
		int ans1 = DP(1, 0, 0, 1);
		MEM(dp, -1);
		int ans2 = DP(1, 0, 0, 0);
		printf("Case %d: %d %d\n", ++ks, (ans1 + MOD - ans2) % MOD, ans2);
	}

	AIN(ks, 1, 20);
	return 0;
}
