// Rujia Liu
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const long long BIG = 1000000;
const int maxn = 200000;
long long d[maxn];
int W[3][10];

inline void update(int y, int i, long long w) {
  if(i <= y && (d[i] < 0 || w < d[i])) {
    d[i] = w;
  }
}

long long solve(int x, int y) {
  memset(d, -1, sizeof(d));
  d[x] = 0;
  for(int i = x; i < y; i++) {
    for(int j = 0; j <= 9; j++) {
      update(y, i*10+j, d[i] + BIG * W[0][j] + 1);
      if(j > 0) update(y, i+j, d[i] + BIG * W[1][j] + 1);
      if(j > 1) update(y, i*j, d[i] + BIG * W[2][j] + 1);
    }
  }
  return d[y];
}

int main() {
  int x, y, kase = 0;
  while(scanf("%d%d", &x, &y) == 2) {
    for(int i = 0; i < 3; i++)
      for(int j = 0; j <= 9; j++) scanf("%d", &W[i][j]);
    long long s = solve(x, y);
    s = min(s, solve(0, y) + BIG * W[2][0] + 1);
    printf("Case %d: %d %d\n", ++kase, (int)(s / BIG), (int)(s % BIG));
  }
  return 0;
}
