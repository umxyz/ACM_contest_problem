// Rujia Liu
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;

const int maxn = 2000 + 10;
const int INF = 1000000000;

struct Edge {
  int from, to, cap, flow, cost;
  Edge(int u, int v, int c, int f, int w):from(u),to(v),cap(c),flow(f),cost(w) {}
};

struct MCMF {
  int n, m;
  vector<Edge> edges;
  vector<int> G[maxn];
  int inq[maxn];         // �Ƿ��ڶ�����
  int d[maxn];           // Bellman-Ford
  int p[maxn];           // ��һ����
  int a[maxn];           // �ɸĽ���

  void init(int n) {
    this->n = n;
    for(int i = 0; i < n; i++) G[i].clear();
    edges.clear();
  }

  void AddEdge(int from, int to, int cap, int cost) {
    edges.push_back(Edge(from, to, cap, 0, cost));
    edges.push_back(Edge(to, from, 0, 0, -cost));
    m = edges.size();
    G[from].push_back(m-2);
    G[to].push_back(m-1);
  }

  bool BellmanFord(int s, int t, int flow_limit, int& flow, int& cost) {
    for(int i = 0; i < n; i++) d[i] = INF;
    memset(inq, 0, sizeof(inq));
    d[s] = 0; inq[s] = 1; p[s] = 0; a[s] = INF;

    queue<int> Q;
    Q.push(s);
    while(!Q.empty()) {
      int u = Q.front(); Q.pop();
      inq[u] = 0;
      for(int i = 0; i < G[u].size(); i++) {
        Edge& e = edges[G[u][i]];
        if(e.cap > e.flow && d[e.to] > d[u] + e.cost) {
          d[e.to] = d[u] + e.cost;
          p[e.to] = G[u][i];
          a[e.to] = min(a[u], e.cap - e.flow);
          if(!inq[e.to]) { Q.push(e.to); inq[e.to] = 1; }
        }
      }
    }
    if(d[t] == INF) return false;
    if(flow + a[t] > flow_limit) a[t] = flow_limit - flow;
    flow += a[t];
    cost += d[t] * a[t];
    for(int u = t; u != s; u = edges[p[u]].from) {
      edges[p[u]].flow += a[t];
      edges[p[u]^1].flow -= a[t];
    }
    return true;
  }

  // ��Ҫ��֤��ʼ������û�и�ȨȦ
  int MincostFlow(int s, int t, int flow_limit, int& cost) {
    int flow = 0; cost = 0;
    while(flow < flow_limit && BellmanFord(s, t, flow_limit, flow, cost));
    return flow;
  }

};

MCMF g;

int main() {
  int kase = 0, n, m, u, v, d, a;
  while(scanf("%d%d", &n, &m) == 2 && n) {
    assert(n >= 1 && n <= 500 && m >= 1 && m <= 2000);
    g.init(n);

    while(m--) {
      scanf("%d%d%d%d", &u, &v, &d, &a);
      assert(1<=u && u<=n && 1<=v && v<=n && 1<=d && d<=1000 && 0<=a && a<=1000);
      if(u != v) {
        u--; v--;
        g.AddEdge(u, v, 1, d);
        g.AddEdge(u, v, 1, d+a);
      }
    }
    int cost;
    g.MincostFlow(0, n-1, 2, cost);
    printf("Case %d: %d\n", ++kase, cost);
  }
  return 0;
}
