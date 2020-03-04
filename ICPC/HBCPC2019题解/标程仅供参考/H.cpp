#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 100005;
char f[N];

#define ck(x, l, r)           \
    if ((x < l) || (x > r)) { \
        return 0;             \
    }

int main(int argc, char* argv[]) {
    if (argc == 3) {
        freopen(argv[1], "r", stdin);
        freopen(argv[2], "w", stdout);
    }
    int T;
    scanf("%d", &T);
    ck(T, 1, 20);
    while (T--) {
        int k;
        int ans = 0;
        scanf("%d%d", &ans, &k);
        ck(ans, 1, 1e9);
        ck(k, 1, 100);
        // for(int i=1;i<=len;i++)
        // {
        // 	ans=(ans*10+f[i]-'0')%9;
        // }
        int x = ans % 9;
        ans = 1;
        for (int i = 1; i <= k; i++) ans = (ans * x) % 9;
        if (ans == 0) ans = 9;
        printf("%d\n", ans);
    }
    return 0;
}
