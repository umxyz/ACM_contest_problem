#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 5;

int n, m, t;

int a[maxn];
int b[maxn];

struct bittree {
    int tree[maxn];

    int lowbit(int x) { return x & -x; }

    int sum(int p) {
        int ret = 0;
        while (p) {
            ret += tree[p];
            p -= lowbit(p);
        }
        return ret;
    }

    int update(int p, int x) {
        while (p <= n) {
            tree[p] += x;
            p += lowbit(p);
        }

        return 0;
    }

    int query(int l, int r) {
        if (l > r) {
            return 0;
        }
        return sum(r) - sum(l - 1);
    }

    int init() {
        memset(tree, 0, sizeof(tree));
        return 0;
    }
} tree[2];

int read() {
    int x;
    scanf("%d", &x);
    return x;
}

#define ck(x, l, r) if((x < l) || (x > r)) {\
 return 0;}

int main() {
    int i, j;

    n = read();
    ck(n, 1, 1e5);

    tree[0].init();
    tree[1].init();

    for (i = 1; i <= n; i++) {
        b[read()] = i;
        a[i] = read();
        ck(a[i], n, 2 * n);
        tree[1].update(i, 1);
    }

    for (i = 1; i <= n; i++) {
        tree[1].update(b[a[i]], -1);
        tree[0].update(b[a[i]], 1);

        printf("%d\n",
               tree[0].query(b[a[i]] + 1, n) + tree[1].query(1, b[a[i]] - 1));
    }

    return 0;
}