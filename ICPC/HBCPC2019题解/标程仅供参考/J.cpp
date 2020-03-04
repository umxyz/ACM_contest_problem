#include <bits/stdc++.h>

template <class T>
bool Enlarge(T &a, T const &b) {
    return a < b ? a = b, 1 : 0;
}

const int XN = 1e6 + 11, INF = 0x1f1f1f1f;

int fa[XN];
std::vector<int> G[XN];
bool on[XN], ud[XN];
int f[XN][2], pre[XN];  // 0能用 1不能用  f[pos][0]<=f[pos][1]
void DP(int pos) {
    ud[pos] = 1;

    for (auto u : G[pos])
        if (!on[u]) {
            DP(u);
            f[pos][0] += f[u][1];
        }
    for (auto u : G[pos])
        if (!on[u] && Enlarge(f[pos][1], f[pos][0] + f[u][0] - f[u][1] + 1))
            pre[pos] = u;
    Enlarge(f[pos][1], f[pos][0]);
}

std::vector<std::pair<int, int>> Ans;

void Construct(int pos, int d) {
    if (f[pos][0] == f[pos][1]) d = 0;
    if (d == 0) {
        for (auto u : G[pos])
            if (!on[u]) Construct(u, 1);
    } else {
        Ans.push_back({pre[pos], pos});
        Construct(pre[pos], 0);
        for (auto u : G[pos])
            if (!on[u] && u != pre[pos]) Construct(u, 1);
    }
}

void Solve(int r) {
    static bool fc[XN];
    static int stack[XN], top, circle[XN], cc;
    top = cc = 0;
    while (!fc[r]) {
        stack[++top] = r;
        fc[r] = 1;
        r = fa[r];
    }
    while (stack[top + 1] != r) on[circle[++cc] = stack[top--]] = 1;
    static int g[XN][2][2];
    for (int i = 1; i <= cc; ++i) {
        DP(circle[i]);  // i..
        for (int d1 = 0; d1 < 2; ++d1)
            for (int d2 = 0; d2 < 2; ++d2) g[i][d1][d2] = -INF;
    }
    g[1][0][0] = g[1][0][1] = f[circle[1]][0];
    g[1][1][1] = f[circle[1]][1];
    g[1][1][0] = -INF;
    for (int i = 2; i <= cc; ++i)
        for (int d1 = 0; d1 < 2; ++d1) {
            Enlarge(g[i][d1][0], g[i - 1][d1][1] + f[circle[i]][0]);
            Enlarge(g[i][d1][1], g[i - 1][d1][1] + f[circle[i]][1]);
            Enlarge(g[i][d1 ^ (i == 2 && d1 == 0)][1],
                    g[i - 1][d1][0] + 1 + f[circle[i]][0]);
            Enlarge(g[i][d1][1], g[i][d1][0]);
            // g[i][d1][0]<=g[i][d1][1] 0能 1 不能用
        }
    int res = -INF, r1, r2;
    for (int d1 = 0; d1 < 2; ++d1)
        for (int d2 = 0; d2 < 2; ++d2)
            if (Enlarge(res, g[cc][d1][d2] + (!d1 && !d2))) {
                r1 = d1;
                r2 = d2;
            }

    if (!r1 && !r2) Ans.push_back({circle[1], circle[cc]});
    for (int i = cc; i >= 1; --i) {
        if (g[i][r1][0] == g[i][r1][1]) r2 = 0;
        if (r2 == 0) {
            Construct(circle[i], 0);
            r2 = 1;
        } else {
            if (g[i][r1][1] ==
                g[i - 1][r1 ^ (r1 == 1 && i == 2)][0] + 1 + f[circle[i]][0]) {
                Ans.push_back({circle[i - 1], circle[i]});
                Construct(circle[i], 0);
                r2 = 0;
            } else {
                Construct(circle[i], 1);
                r2 = 1;
            }
        }
    }
}

#define ck(x, l, r)           \
    if ((x < l) || (x > r)) { \
        return 0;             \
    }


int main() {
    // freopen("input","r",stdin);
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int n;
    std::cin >> n;
	ck(n, 2, 1e6);
    for (int i = 1; i <= n; ++i) {
        std::cin >> fa[i];
		ck(fa[i], 1, n);
        G[fa[i]].push_back(i);
    }
    for (int i = 1; i <= n; ++i)
        if (!ud[i]) Solve(i);

    std::cout << n - 2 * Ans.size() << '\n';
    /*
    for(auto p : Ans)
            std::cout<<p.first<<' '<<p.second<<'\n';
            */
    return 0;
}
