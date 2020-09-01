// Rujia Liu
#include<cstdio>
#include<cassert>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100*2 + 5;
const int maxv = 10000 + 5;
const int RIGHT = 0;
const int UP = 1;

int line[maxn][maxn][2]; // RIGHT and UP
int alive[maxn][maxn]; // alive[x][y] == 1 iff the square whose left-bottom corner is (x,y), is alive

int npx, npy; // number of points in x and y directions. points are numbered 1 to np*. squares are numbered 0 to np*
int xp[maxn], yp[maxn], idx[maxv], idy[maxv]; // xp[idx[v]] = v.

void dfs(int x, int y) {
  if(alive[x][y]) return;
  alive[x][y] = 1;
  if(y < npy && !line[x][y+1][RIGHT]) dfs(x, y+1); // UP
  if(y > 0   && !line[x][y  ][RIGHT]) dfs(x, y-1); // DOWN
  if(x > 0   && !line[x][y  ][UP]) dfs(x-1, y); // LEFT
  if(x < npx && !line[x+1][y][UP]) dfs(x+1, y); // RIGHT
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    int n, x1[maxn], y1[maxn], x2[maxn], y2[maxn], vis[maxv];
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
      scanf("%d%d%d%d", &x1[i], &y1[i], &x2[i], &y2[i]);
      if(x1[i] == x2[i]) {
        assert(y1[i] != y2[i]);
        if(y1[i] > y2[i]) swap(y1[i], y2[i]);
      } else {
        assert(y1[i] == y2[i]);
        if(x1[i] > x2[i]) swap(x1[i], x2[i]);
      }
    }

    // discrete x
    memset(vis, 0, sizeof(vis));
    for(int i = 0; i < n; i++) vis[x1[i]] = vis[x2[i]] = 1;
    npx = 0;
    for(int i = 0; i < maxv; i++) if(vis[i]) {
      xp[++npx] = i;
      idx[i] = npx;
    }
    
    // discrete y
    memset(vis, 0, sizeof(vis));
    for(int i = 0; i < n; i++) vis[y1[i]] = vis[y2[i]] = 1;
    npy = 0;
    for(int i = 0; i < maxv; i++) if(vis[i]) {
      yp[++npy] = i;
      idy[i] = npy;
    }

    // draw lines in discrete grid
    memset(line, 0, sizeof(line));
    for(int i = 0; i < n; i++) {
      if(x1[i] != x2[i]) for(int x = idx[x1[i]]; x < idx[x2[i]]; x++) line[x][idy[y1[i]]][RIGHT] = 1;
      if(y1[i] != y2[i]) for(int y = idy[y1[i]]; y < idy[y2[i]]; y++) line[idx[x1[i]]][y][UP] = 1;
    }

    // floodfill
    memset(alive, 0, sizeof(alive));
    dfs(0, 0);

    // accumulate answer
    int ans = 0;
    int lost = 0;
    for(int x = 1; x <= npx; x++)
      for(int y = 1; y <= npy; y++) {
        if(!alive[x][y]) lost++;
        if(line[x][y][RIGHT] && (alive[x][y] || alive[x][y-1])) ans += xp[x+1] - xp[x]; // check RIGHT
        if(line[x][y][UP]    && (alive[x][y] || alive[x-1][y])) ans += yp[y+1] - yp[y]; // check UP
      }
    printf("%d\n", ans);
  }
  return 0;
}
