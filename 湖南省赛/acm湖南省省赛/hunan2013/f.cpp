// Rujia Liu
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

const int maxn = 300 + 5;
const int maxm = 50000 + 5;
const int INF = 1000000000;

struct Edge {
  int u, v, a, b, t;
} e[maxm];
vector<int> edges[maxn];
int n, m, s, t, d[maxn], mark[maxn];

void update(int u, Edge& e0) {
  if(e0.a < e0.t) return;
  int t0 = d[u] % (e0.a + e0.b);
  int newd;
  if(t0 + e0.t <= e0.a) newd = d[u] + e0.t;
  else newd = d[u] - t0 + e0.a + e0.b + e0.t;
  d[e0.v] = min(d[e0.v], newd);
}

int solve() {
  if(s == t) return 0;
  memset(mark, 0, sizeof(mark));
  for(int i = 1; i <= n; i++) d[i] = INF;
  d[s] = 0;
  while(!mark[t]) {
    int u = -1;
    for(int i = 1; i <= n; i++)
      if(!mark[i] && (u < 0 || d[i] < d[u])) u = i;
    if(u < 0) break;
    mark[u] = 1;
    for(int i = 0; i < edges[u].size(); i++) {
      // start at time d[i], using edge e[edges[u][i]]
      update(u, e[edges[u][i]]);
    }
  }
  return d[t];
}

int main() {
  int kase = 0;
  while(scanf("%d%d%d%d", &n, &m, &s, &t) == 4) {
    for(int i = 1; i <= n; i++) edges[i].clear();
    for(int i = 0; i < m; i++) {
      scanf("%d%d%d%d%d", &e[i].u, &e[i].v, &e[i].a, &e[i].b, &e[i].t);
      edges[e[i].u].push_back(i);
    }
    int ans = solve();
    printf("Case %d: %d\n", ++kase, ans == INF ? -1 : ans);
  }
  return 0;
}
