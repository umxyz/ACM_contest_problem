// 陈锋
#include<cassert>
#include<climits>
#include<cstdlib>
#include<iostream>
#include<functional>
#include<algorithm>
#include<cstring>
#include<string>
#include<sstream>
#include<vector>
#include<ctime>
#include<cstdio>
using namespace std;
struct Point {
	int x, y;
	Point(int x = 0, int y = 0) :x(x), y(y) {}
};
typedef Point Vector;

const int MAXN = 1000 + 4;
char CMD[MAXN];
Vector DIRS[4];
int n;

void init() {
	DIRS[0].x = 1; DIRS[0].y = 0;
	DIRS[1].x = 0; DIRS[1].y = 1;
	DIRS[2].x = -1; DIRS[2].y = 0;
	DIRS[3].x = 0; DIRS[3].y = -1;
}

struct Ans {
	int minX, minY, maxX, maxY;
	Ans& update(const Ans& a) {
		minX = min(minX, a.minX); minY = min(minY, a.minY);
		maxX = max(maxX, a.maxX); maxY = max(maxY, a.maxY);
        return *this;
	}

	Ans& operator=(const Ans& a) {
		minX = a.minX; minY = a.minY;
		maxX = a.maxX; maxY = a.maxY;
		return *this;
	}

	Ans operator+(const Vector& v) const {
		Ans a = *this;
		a.minX += v.x; a.minY += v.y;
		a.maxX += v.x; a.maxY += v.y;
		return a;
	}
};

ostream& operator<<(ostream& os, const Ans& a) {
	char buf[64];
	sprintf(buf, "x(%d,%d),y(%d,%d)", a.minX, a.maxX, a.minY, a.maxY);
	return os << buf;
}

Ans DP[4][MAXN];

// DP(d, i) 表示当前方向为DIRS中的(0,1,2,3)，剩下i个指令要执行，X，Y分别能走出的差量
int main()
{
	init();
	for (int t = 1; scanf("%s", CMD) == 1; t++) {
		n = strlen(CMD);
		memset(DP, 0, sizeof(DP));

		for (int i = 1; i <= n; i++) { // 还剩i个指令        
			char c = CMD[n - i];
			for (int d = 0; d < 4; d++) { // 当前的方向
				int nd; Point next;
				Ans& a = DP[d][i];
				Ans al = DP[(d + 1) % 4][i - 1],
					ar = DP[(d - 1 + 4) % 4][i - 1],
					af = DP[d][i - 1] + DIRS[d];
				if (c == 'L') a = al;
				else if (c == 'R') a = ar;
				else if (c == 'F') a = af;
				else {
					assert(c == '?');
					a = al.update(ar).update(af);
				}
			}
		}          

		Ans& a = DP[0][n];
		printf("Case %d: %d %d %d %d\n", t, a.minX, a.maxX, a.minY, a.maxY);
	}
	return 0;
}
