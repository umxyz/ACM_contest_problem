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

VI V[305];
int w[305][305];
VP E;
int n;

int input(int ks)
{
	int i, node, u;
	char word[20];

	E.clear();
	for(i = 1; i <= 300; i++) V[i].clear();

	int input = 0;
	while(scanf("%d", &node) != EOF)
	{
		if(node == 0) break;

		input = 1;
		while(scanf("%s", word))
		{
			if(word[0] == '0') break;
			char dir = '.';
			int len = strlen(word);
			if(!IN(word[len - 1], '0', '9')) dir = word[len - 1], word[len - 1] = 0;
			sscanf(word, "%d", &u);

			if(dir == '.')
			{
				V[node].push_back(u);
				V[u].push_back(node);
				w[node][u] = w[u][node] = 0;
				E.push_back(PII(node, u));
			}
			else if(dir == 'u')
			{
				V[node].push_back(u);
				V[u].push_back(node);
				w[node][u] = 2, w[u][node] = 1;
			}
			if(dir == 'd')
			{
				V[node].push_back(u);
				V[u].push_back(node);
				w[node][u] = 1, w[u][node] = 2;
			}
		}
	}

	for(i = 1; i <= 300; i++) if(SZ(V[i])) n = i;

	AIN(n, 1, 300);

	return input;
}

int dfs(int at, int depth, int parent)
{
	int ret = depth;
	for(int i = 0; i < SZ(V[at]); i++)
		if(V[at][i] != parent && w[at][V[at][i]] == 1)
		{
			int now = dfs(V[at][i], depth + 1, at);
			ret = MAX(ret, now);
		}

	return ret;
}

int calcChain()
{
	int ret = 1;
	for(int i = 1; i <= n; i++)
	{
		int now = dfs(i, 1, 0);
		ret = MAX(ret, now);
	}

	return ret;
}

int DP2(int at, int parent, int depth, int L);

int dp1[305];
int DP1(int at, int parent, int L)
{
	int &ret = dp1[at];
	if(ret != -1) return ret;
	ret = 1000000000;

	for(int i = 1; i <= L; i++)
	{
		int now = DP2(at, parent, i, L);
		ret = MIN(ret, now);
	}
	return ret;
}

int dp2[305][305];
int DP2(int at, int parent, int depth, int L)
{
	if(depth < 1 || depth > L) return 1000000000;

	int &ret = dp2[at][depth];
	if(ret != -1) return ret;
	ret = 0;

	for(int i = 0; i < SZ(V[at]); i++)
		if(V[at][i] != parent)
		{
			int u = V[at][i];
			int cost = 1000000000;

			for(int d = 1; d <= L; d++)
			{
				if(w[at][u] == 1 && d < depth)
				{
					int now = DP2(u, at, d, L);
					cost = MIN(cost, now);
				}
				else if(w[at][u] == 2 && d > depth)
				{
					int now = DP2(u, at, d, L);
					cost = MIN(cost, now);
				}
				else if(w[at][u] == 0 && d != depth)
				{
					int now = DP2(u, at, d, L);
					cost = MIN(cost, now);
				}
			}

			if(w[at][u] == 0)
			{
				int now = 1 + DP1(u, at, L);
				cost = MIN(cost, now);
			}

			ret = MIN(1000000000, ret + cost);
		}

	return ret;
}

int calcAns(int L)
{
	MEM(dp1, -1);
	MEM(dp2, -1);

	return DP1(1, 0, L);
}

int main()
{
	int ks = 0;

	while(input(ks))
	{
		int L = calcChain();
		int minAns = calcAns(L);
		printf("Case %d: %d", ++ks, SZ(E) - minAns);
		for(int i = 0; i < SZ(E); i++)
		{
			w[E[i].first][E[i].second] = 1;
			w[E[i].second][E[i].first] = 2;
			int now = calcAns(L);

			if(now == minAns) {printf(" (%d,d)", i + 1); continue;}

			w[E[i].first][E[i].second] = 2;
			w[E[i].second][E[i].first] = 1;
			now = calcAns(L);

			if(now == minAns) {printf(" (%d,u)", i + 1); continue;}

			w[E[i].first][E[i].second] = 0;
			w[E[i].second][E[i].first] = 0;
		}
		printf("\n");
	}

	return 0;
}
