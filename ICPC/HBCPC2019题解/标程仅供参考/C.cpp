#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 105;
long long f[N][N];
int cost[N], n;
#define ck(x, l, r) if((x < l) || (x > r)) {\
 return 0;}

int main() {
    int T;
    scanf("%d", &T);
    ck(T,1,50);
    while (T--) {
        scanf("%d", &n);
        ck(n, 1, 100);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &cost[i]);
            ck(cost[i], 1, 10000);
        }
        memset(f, 0x3f, sizeof f);
        for (int i = 1; i <= n; i++) f[i][i] = 0;
        for (int len = 2; len <= n; len++)
            for (int l = 1; l + len <= n + 1; l++) {
                int r = l + len - 1;
                for (int i = l + 1; i <= r - 1; i++) {
                    f[l][r] = min(
                        f[l][r], f[l][i - 1] + f[i + 1][r] + (r - l) * cost[i]);
                }
                f[l][r] =
                    min(f[l][r], f[l][l] + f[l + 1][r] + (r - l) * cost[l]);
                f[l][r] =
                    min(f[l][r], f[r][r] + f[l][r - 1] + (r - l) * cost[r]);
            }
        printf("%lld\n", f[1][n]);
    }
}