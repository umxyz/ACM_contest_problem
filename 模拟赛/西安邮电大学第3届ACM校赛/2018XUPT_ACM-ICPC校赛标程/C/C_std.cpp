#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int  MAXN = 41000;
const int  MAXM = 10000010;
const int  INF  = 0x3f3f3f3f;


int dir[8][2]={ {1,1},{1,-1},{-1,1},{-1,-1} , {2,2},{2,-2},{-2,2},{-2,-2}  };


inline int read(){int ra,fh;char rx;rx=getchar(),ra=0,fh=1;
while((rx<'0'||rx>'9')&&rx!='-')rx=getchar();if(rx=='-')
fh=-1,rx=getchar();while(rx>='0'&&rx<='9')ra*=10,ra+=rx-48,
rx=getchar();return ra*fh;}


struct Edge
{
    int from, to, cap, flow, next;
};
Edge edge[MAXM];
int head[MAXN], cur[MAXN], edgenum;
int dist[MAXN];
bool vis[MAXN];
int N, M,ss,tt;
void init()
{
    edgenum = 0;
    memset(head, -1, sizeof(head));
}
void addEdge(int u, int v, int w)
{
    Edge E1 = {u, v, w, 0, head[u]};
    edge[edgenum] = E1;
    head[u] = edgenum++;
    Edge E2 = {v, u, 0, 0, head[v]};
    edge[edgenum] = E2;
    head[v] = edgenum++;
}

bool BFS(int s, int t)
{
    queue<int> Q;
    memset(dist, -1, sizeof(dist));
    memset(vis, false, sizeof(vis));
    dist[s] = 0;
    vis[s] = true;
    Q.push(s);
    while(!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for(int i = head[u]; i != -1; i = edge[i].next)
        {
            Edge E = edge[i];
            if(!vis[E.to] && E.cap > E.flow)
            {
                dist[E.to] = dist[u] + 1;
                if(E.to == t) return true;
                vis[E.to] = true;
                Q.push(E.to);
            }
        }
    }
    return false;
}
int DFS(int x, int a, int t)
{
    if(x == t || a == 0) return a;
    int flow = 0, f;
    for(int &i = cur[x]; i != -1; i = edge[i].next)
    {
        Edge &E = edge[i];
        if(dist[E.to] == dist[x] + 1 && (f = DFS(E.to, min(a, E.cap - E.flow), t)) > 0)
        {
            edge[i].flow += f;
            edge[i^1].flow -= f;
            flow += f;
            a -= f;
            if(a == 0) break;
        }
    }
    return flow;
}
int Maxflow(int s, int t)
{
    int flow = 0;
    while(BFS(s, t))
    {
        memcpy(cur, head, sizeof(head));
        flow += DFS(s, INF, t);
    }
    return flow;
}


int mm[205][205];
int m,n;
int u,v;

int getnum(int x,int y)
{
    return (x-1)*n+y;
}


void dfs(int curx,int cury,int now)
{
    mm[curx][cury] = now;
    for(int i=0 ;i<8;i++)
    {
        int xx = curx + dir[i][0];
        int yy = cury + dir[i][1];
        if(xx<1||xx>n||yy<1||yy>n||mm[xx][yy])
        {
            continue;
        }
        if(now==2)
        {
            dfs(xx,yy,3);
        }
        else
        {
            dfs(xx,yy,2);
        }
    }
}


int main()
{

   // ios_base::sync_with_stdio(false);
    cin >> n>>m;
    init();
    int s = 0;
    int t = n*n+1;
    for(int i=0;i<m;i++)
    {
        cin >> u>>v;
        mm[u][v]=1;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(mm[i][j]==0)
            {
                dfs(i,j,2);
            }
        }
    }


    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(mm[i][j]==2)
            {
                addEdge(s,getnum(i,j),1);
                for(int d=0 ;d<8;d++)
                {
                    int xx = i + dir[d][0];
                    int yy = j + dir[d][1];
                    if(xx<1||xx>n||yy<1||yy>n)
                    {
                        continue;
                    }
                    if(mm[xx][yy]==3)
                    {
                        addEdge(getnum(i,j),getnum(xx,yy),INF);
                    }
                }

            }
            if(mm[i][j]==3)
            {
                addEdge(getnum(i,j),t,1);
            }
        }
    }

    cout << n*n-m-Maxflow(s,t)<<endl;

    return 0;
}
