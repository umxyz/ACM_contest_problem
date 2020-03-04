#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
long long work(long long q, long long x, long long p, long long &qx) {
    if (x == 1) {
        qx = q % p;
        return q % p;
    }
    long long y = x / 2, qy = 0;
    long long ret = work(q, y, p, qy);
    ret = (ret + (ret * qy) % p) % p;
    qx = (qy * qy) % p;
    if (x % 2 == 1) {
        qx = (qx * q) % p;
        ret = (ret + qx) % p;
    }
    return ret;
}
#define ck(x, l, r) ((x < l) || (x > r))

int main() {
    int T, q, n, p;
    scanf("%d", &T);
    if (ck(T, 1, 100)) {
        return 0;
    }
    while (T--) {
        scanf("%d%d%d", &q, &n, &p);
        if(ck(n, 1, 1e9) || ck(q, 1, 1e9) || ck(p, 1, 1e9)) {
            return 0;
        }
        long long tt = 0;
        printf("%lld\n", work(q, n, p, tt));
    }
    return 0;
}
