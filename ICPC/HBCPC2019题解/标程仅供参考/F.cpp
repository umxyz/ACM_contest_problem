#include <bits/stdc++.h>
using namespace std;

#define ck(x, l, r) if((x < l) || (x > r)) {\
 return 0;}

int main() {
    int m, n, s;
    for (; cin >> m >> n >> s;) {
        ck(s, 1, 1e9);
        ck(m, 1, 1e9);
        ck(n, 1, 1e9);
        if (n >= s + 1)
            cout << "Alice\n";
        else
            cout << (m % (s + 1) == 0 ? "Bob" : "Alice") << '\n';
    }
}