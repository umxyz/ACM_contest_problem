#include <bits/stdc++.h>

const int XN = 60, dx[] = {0, 0, -1, 1}, dy[] = {1, -1, 0, 0};

std::unordered_set<int> S;
int n, a[XN][XN];
void DFS(int x, int y, int num, int dep) {
    S.insert(num);
    if (dep) {
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            if (1 <= nx && nx <= n && 1 <= ny && ny <= n)
                DFS(nx, ny, num * 10 + a[nx][ny], dep - 1);
        }
    }
}

#define ck(x, l, r)           \
    if ((x < l) || (x > r)) { \
        return 0;             \
    }

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cin >> n;
    ck(n, 1, 50);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) std::cin >> a[i][j];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) DFS(i, j, a[i][j], 5);
    int Ans = 0;
    while (S.count(Ans)) Ans++;
    std::cout << Ans << '\n';
    return 0;
}
