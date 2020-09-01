#include<cstdio>
#include<cmath>
#include<cassert>

const int maxn = 100000 + 5;
int n, b, xb, yb, x1[maxn], x2[maxn], Y1[maxn], y2[maxn], s[maxn], d[maxn], t[maxn];

bool intersects(int x1, int Y1, int x2, int y2, int x, double& y) {
 // (y-y1)/(x-x1)=(y1-y2)/(x1-x2)
 // y=y1+(x-x1)(y1-y2)/(x1-x2)
/*
  if(x == x1 || x == x2 || x1 == x2) {
    printf("x=%d, x1=%d, x2=%d\n", x, x1, x2);
  }
*/
  assert(x1 != x2);
  if(x < x1 || x > x2) return false;
  y = Y1 + (double)(x-x1)*(Y1-y2)/(x1-x2);
  return true;
}

int drop(int xb, int yb) {
  double maxy = 0;
  int ans = -1;
  for(int i = 0; i < n; i++) {
    double y;
    if(t[i] == 0 && intersects(x1[i], Y1[i], x2[i], y2[i], xb, y)) {
//printf("i=%d, yb=%d, y=%.2lf\n", i, yb, y);
      if(fabs(y - yb) < 0.1) {
        fprintf(stderr, "%d %d %d %d - %d %d\n", x1[i], Y1[i], x2[i], y2[i], xb, yb);
      }
      if(y < yb && y > maxy) { maxy = y; ans = i; }
    }
  }
//printf("hit=%d\n", ans);
  if(ans < 0) return 0;
  assert(xb != x1[ans] && xb != x2[ans]);
  t[ans] = d[ans];
  return s[ans];
}

char mode;

bool isgen() { return mode == 'g'; }
bool israw() { return mode == 'r'; }
bool isdefault() { return mode == 'd'; }

int main(int argc, char* argv[]) {
  int kase = 0;
  mode = 'd'; // default
  if(argc > 1) mode = argv[1][0];

  while(scanf("%d", &n) == 1) {
    if(isgen()) printf("%d\n", n);

    for(int i = 0; i < n; i++) {
      scanf("%d%d%d%d%d%d", &x1[i], &Y1[i], &x2[i], &y2[i], &s[i], &d[i]);
      assert(x1[i] >= 0 && x1[i] < x2[i] && x2[i] <= 1000000000);
      assert(Y1[i] >= 1 && Y1[i] <= 200000 && y2[i] >= 1 && y2[i] <= 200000 && s[i] >= 1 && s[i] <= 1000 && d[i] >= 1 && d[i] <= 5);
      t[i] = 0;
      if(isgen()) printf("%d %d %d %d %d %d\n", x1[i], Y1[i], x2[i], y2[i], s[i], d[i]);
    }

    scanf("%d", &b);
    if(isgen()) printf("%d\n", b);

    int score = 0;
    if(!isgen()) printf("Case %d:\n", ++kase);

    while(b--) {
      scanf("%d%d", &xb, &yb);

      if(isgen()) printf("%d %d\n", xb^score, yb^score);

      if(isdefault()) { xb ^= score; yb ^= score; }
//      printf("--> %d %d\n", xb, yb);
      assert(xb >= 0 && xb <= 1000000000 && yb > 0 && yb <= 200000);
      score += drop(xb, yb);
      if(!isgen()) printf("%d\n", score);
      for(int i = 0; i < n; i++) { if(t[i]) t[i]--; }
    }
    if(!isgen()) printf("\n");
  }
  return 0;
}
