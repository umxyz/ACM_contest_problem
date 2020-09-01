// Rujia Liu
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 16 + 5;
const int maxm = 100 + 5;
const int INF = 1000000000;
int n, m;

int pa[maxn];
int findset(int x) { return pa[x] != x ? pa[x] = findset(pa[x]) : x; } 

struct Edge {
  int u, v, c;
  bool operator < (const Edge& rhs) const {
    return c < rhs.c;
  }
};

Edge e[maxm];

int MST() {
  sort(e, e+m);
  for(int i = 0; i < n; i++) pa[i] = i;
  int cnt = 0;
  int ans = 0;
  for(int i = 0; i < m; i++) {
    int u = e[i].u, v = e[i].v;
    u = findset(u);
    v = findset(v);
    int c = e[i].c;
    if(u != v) {
      pa[u] = v;
      ans += c;
      if(++cnt == n-1) return ans;
    }
  }
  return INF;
}

int in, im, K;
Edge ie[maxm];
int p[maxn];
int id[maxn];

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%d%d%d", &in, &im, &K);
    int p[maxn];
    Edge ie[maxn*maxn];
    for(int i = 0; i < in; i++) scanf("%d", &p[i]);
    for(int i = 0; i < im; i++) {
      int u, v, c;
      scanf("%d%d%d", &u, &v, &c);
      ie[i] = (Edge){ u-1, v-1, c };
    }

    int ans = p[0];
    int bestn = 1;
    for(int S = 0; S < (1<<(in-1)); S++) {
      n = 1;
      m = 0;
      memset(id, -1, sizeof(id));
      id[0] = 0; // capital
      for(int i = 0; i < in-1; i++)
        if(S & (1<<i)) id[i+1] = n++;
      for(int i = 0; i < im; i++) {
        int u = id[ie[i].u];
        int v = id[ie[i].v];
        if(u >= 0 && v >= 0) e[m++] = (Edge) { u, v, ie[i].c };
      }
      if(MST() <= K) {
        int tot = p[0];
        for(int i = 0; i < in-1; i++)
          if(S & (1<<i)) tot += p[i+1];
        if(tot > ans) { bestn = n; }
        ans = max(ans, tot);        
      }
    }

    printf("%d\n", ans);
  }
  return 0;
}
