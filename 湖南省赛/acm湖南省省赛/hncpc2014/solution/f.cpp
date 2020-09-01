#pragma warning(disable:4786)
#pragma warning(disable:4996)
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

//typedef int LL;
typedef long long int LL;
//typedef __int64 LL;

int R, C;
char grid[35][35];
int vis[35][35];
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};
int adj[35][35];
int color[35];

void dfs(int r, int c, int marker)
{
	vis[r][c] = marker;
	int d, rd, cd;
	FORN(d, 4)
	{
		rd = r + dr[d];
		cd = c + dc[d];
		if(rd < 0 || rd >= R || cd < 0 || cd >= C || vis[rd][cd] || grid[r][c] != grid[rd][cd]) continue;
		dfs(rd, cd, marker);
	}
}

LL ans = 0;
void process(int mask, int nRegion)
{
	LL z = 1;
	int i, j;
	for(int bit = 0; bit <= 1; bit++)
	{
		FORAB(i, 1, nRegion) color[i] = 0;

		FORAB(i, 1, nRegion)
			if(((mask >> (i - 1)) & 1) == bit)
				color[i] = 1;

		int allSingle = 1;
		int nComponent = 0;
		FORAB(i, 1, nRegion)
			if(color[i] == 1)
			{
				nComponent++;
				int bicolor = 1;
				queue<int> Q;
				Q.push(i);
				color[i] = 2;
				while(!Q.empty())
				{
					int u = Q.front();
					Q.pop();

					FORAB(j, 1, nRegion) if(u != j && adj[u][j] && color[j] != 0)
					{
						allSingle = 0;
						if(color[j] == color[u]) bicolor = 0;
						else if(color[j] != 1) ;
						else
						{
							color[j] = color[u] ^ 2 ^ 3;
							Q.push(j);
						}
					}
				}

				if(bicolor == 0) z = 0;
			}

		if(nComponent == 0) z = 0;
		if(allSingle) z *= (1LL << nComponent) - 2;
		else z *= 1LL << nComponent;
	}
	ans += z;
}

void bktk(int at, int taken, int mask, int nRegion)
{
	if(at == nRegion + 1 || taken == 5)
	{
		process(mask, nRegion);
		return;
	}

	bktk(at + 1, taken, mask, nRegion);
	bktk(at + 1, taken + 1, mask | (1 << (at - 1)), nRegion);
}

void buildGraph()
{
	int i, j;
	CLR(adj);
	FORN(i, R) FORN(j, C)
	{
		if(i < R - 1) adj[vis[i][j]][vis[i + 1][j]] = adj[vis[i + 1][j]][vis[i][j]] = 1;
		if(j < C - 1) adj[vis[i][j]][vis[i][j + 1]] = adj[vis[i][j + 1]][vis[i][j]] = 1;
	}
}

int main()
{
	int i, j, ks = 0;
	int marker;

	while(scanf("%d %d", &R, &C) != EOF)
	{
		AIN(R, 1, 20);
		AIN(C, 1, 20);
		FORN(i, R) scanf("%s", grid[i]);
		
		CLR(vis);
		marker = 0;
		FORN(i, R) FORN(j, C) if(!vis[i][j])
			dfs(i, j, ++marker);

		AIN(marker, 1, 30);
//		fprintf(stderr, "%d\n", marker);
		buildGraph();

		ans = 0;
		bktk(1, 0, 0, marker);
		printf("Case %d: %lld\n", ++ks, ans);
	}

	return 0;
}
