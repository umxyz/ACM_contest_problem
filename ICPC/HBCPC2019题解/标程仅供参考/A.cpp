#include <bits/stdc++.h>
using namespace std;
#define rep(i, j, k) for (int i = int(j); i <= int(k); ++i)
typedef long long LL;
typedef pair<int, int> P;
typedef vector<int> VI;
typedef vector<P> VII;
const int N = 1007;
const double eps = 1e-9;
struct Point {
    long double x, y;
    Point(long double _x = 0, long double _y = 0) : x(_x), y(_y) {}
    Point operator-(const Point &b) { return Point(x - b.x, y - b.y); }
} a[N];
typedef Point Vector;
long double sqr(long double x) { return x * x; }
long double len(Vector a) { return sqr(a.x) + sqr(a.y); }
int cmp(long double x) {
    if (fabs(x) < eps) return 0;
    return x > 0 ? 1 : -1;
}
bool vis1[N], vis2[N];
int main() {
    ios::sync_with_stdio(0);
    int T, n;
    double r;
    cin >> T;
    while (T--) {
        cin >> n >> r;
        r *= 2;
        rep(i, 1, n) cin >> a[i].x >> a[i].y, vis1[i] = false, vis2[i] = false;
        queue<int> Q;
        bool flag = 0;
        rep(i, 1, n) {
            if (cmp(sqr(a[i].x) - sqr(r)) <= 0) {
                vis1[i] = 1;
                Q.push(i);
            }
            if (cmp(sqr(100 - a[i].x) - sqr(r)) <= 0) {
                vis2[i] = 1;
                if (vis1[i]) {
                    flag = 1;
                    break;
                }
            }
        }
        if (flag) {
            cout << "No\n";
            continue;
        }
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            rep(i, 1, n) if (!vis1[i] && cmp(len(a[i] - a[u]) - sqr(r)) <= 0) {
                if (vis2[i]) {
                    flag = 1;
                    break;
                }
                vis1[i] = true;
                Q.push(i);
            }
            if (flag) break;
        }
        if (flag)
            cout << "No\n";
        else
            cout << "Yes\n";
    }
}

/*
2
1 25.0
50.0 50.0
1 25.0
50.0 50.0

*/