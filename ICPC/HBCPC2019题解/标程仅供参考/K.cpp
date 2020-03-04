#include <bits/stdc++.h>

const int XN = 1e3 + 11;
#define ck(x, l, r)           \
    if ((x < l) || (x > r)) { \
        return 0;             \
    }

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    ck(n, 1, 1000);
    ck(m, 1, 1000);
    std::map<std::string, int> rem;
    bool tak = 1;
    static std::string name[XN];
    for (int i = 1; i <= n; ++i) {
        std::string t;
        std::cin >> t;
        ck(t.length(), 1, 20);
        std::cin >> rem[t];
        ck(rem[t], 1, 1e9);
        name[i] = t;
    }
    for (int i = 1; i <= m; ++i) {
        int k;
        std::cin >> k;
        ck(k, 1, 10);
        ck(k, 1, n);
        while (k--) {
            std::string t;
            int need;
            std::cin >> t >> need;
            ck(t.length(), 1, 20);
            ck(need, 1, 1e9);
            if (rem[t] < need) tak = 0;
            rem[t] -= need;
        }
    }
    if (!tak)
        std::cout << "NO" << '\n';
    else {
        std::cout << "YES" << '\n';
        for (int i = 1; i <= n; ++i)
            if (rem[name[i]])
                std::cout << name[i] << ' ' << rem[name[i]] << '\n';
    }
    return 0;
}
