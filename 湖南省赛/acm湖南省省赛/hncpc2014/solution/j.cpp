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

struct Segment
{
	int x1, x2, s, d, y1, y2, ID;
	void input(int i)
	{
		scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &s, &d);
		AIN(x1, 0, x2 - 1);
		AIN(x2, x1 + 1, 1000000000);
		AIN(y1, 1, 200000);
		AIN(y2, 1, 200000);
		AIN(s, 1, 1000);
		AIN(d, 1, 5);
		ID = i;
	}
};

Segment segment[100005];
VI VX;
int used[100005];

struct SegmentTree
{
	VI ids;
};

SegmentTree segmentTree[4 * 200000];
int n;

double calculateY(Segment &segment, int x)
{
	AIN(x, segment.x1, segment.x2);
	//(y - y1) / (y1 - y2) = (x - x1) / (x1 - x2)
	return (1. * x - segment.x1) / (segment.x1 - segment.x2) * (segment.y1 - segment.y2) + segment.y1;
}

struct SegmentComparator
{
	int x;
	SegmentComparator(int _x) 
	{
		x = _x;
	}

	bool operator()(int a, int b)
	{
		double ya = calculateY(segment[a], x);
		double yb = calculateY(segment[b], x);

		return ya > yb;
	}

	bool operator()(double y, int a)
	{
		double ya = calculateY(segment[a], x);
		return ya < y;
	}

	bool operator()(int a, double y)
	{
		double ya = calculateY(segment[a], x);
		return ya > y;
	}
};

void build(int at, int L, int R)
{
	segmentTree[at].ids.clear();

	if(R == L + 1)
		return;

	int M = (L + R) / 2;
	build(2 * at, L, M);
	build(2 * at + 1, M, R);
}

void process(int at, int L, int R)
{
	sort(ALL(segmentTree[at].ids), SegmentComparator(VX[L]));

	if(R == L + 1) return;

	int M = (L + R) / 2;
	process(2 * at, L, M);
	process(2 * at + 1, M, R);
}

int query(int at, int x, int y, int L, int R, int now)
{
	int ret = -1;

	if (R != L + 1)
	{
		int M = (L + R) / 2;
		if(x < VX[M]) ret = query(2 * at, x, y, L, M, now);
		else ret = query(2 * at + 1, x, y, M, R, now);
	}

	vector<int>::iterator it = upper_bound(ALL(segmentTree[at].ids), 1. * y, SegmentComparator(x));
	for(vector<int>::iterator itV = it; itV != segmentTree[at].ids.end(); itV++)
	{
		int id = *itV;
		if(used[id] + segment[id].d > now) continue;
		if(ret == -1) ret = id;
		else if(calculateY(segment[id], x) > calculateY(segment[ret], x)) ret = id;
		break;
	}

	return ret;
}

void insert(int at, int x1, int x2, int L, int R, int id)
{
	if(x1 >= VX[R]) assert(0);
	if(x2 <= VX[L]) assert(0);
	if(x1 <= VX[L] && VX[R] <= x2)
	{
		segmentTree[at].ids.push_back(id);
		return;
	}

	int M = (L + R) / 2;
	if(x1 < VX[M]) insert(2 * at, x1, x2, L, M, id);
	if(x2 > VX[M]) insert(2 * at + 1, x1, x2, M, R, id);
}

int main()
{
	int ks = 0;
	while(scanf("%d", &n) != EOF)
	{
		AIN(n, 1, 100000);
		for(int i = 0; i < n; i++)
		{
			segment[i].input(i);
			used[i] = -1000000000;
		}

		VX.clear();
		VX.push_back(0);
		VX.push_back(2000000000);
		for(int i = 0; i < n; i++)
		{
			VX.push_back(segment[i].x1);
			VX.push_back(segment[i].x2);
		}

		sort(ALL(VX));
		VX.erase(unique(ALL(VX)), VX.end());
		int sz = SZ(VX);

		build(1, 0, sz - 1);

		for(int i = 0; i < n; i++)
			insert(1, segment[i].x1, segment[i].x2, 0, sz - 1, i);

		process(1, 0, sz - 1);

		printf("Case %d:\n", ++ks);

		int nBall, x, y, id;
		scanf("%d", &nBall);
		AIN(nBall, 1, 100000);
		int score = 0;
		for(int i = 0; i < nBall; i++)
		{
			scanf("%d %d", &x, &y);
			x ^= score; y ^= score;
			if(x >= 2000000000) x = 2000000000 - 2;
			AIN(x, 0, 2000000000);
			AIN(y, 0, 1000000000);
			id = query(1, x, y, 0, sz - 1, i);

			if(id != -1) 
			{
				score += segment[id].s;
				used[id] = i;
			}
//			printf("hit=%d\n", segment[id].ID);
			printf("%d\n", score);
		}
		printf("\n");
	}

	AIN(ks, 1, 5);

	return 0;
}
