#include <bits/stdc++.h>

using namespace std;

int n;


#define ck(x, l, r) if((x < l) || (x > r)) {\
 return 0;}

int main() {
    int i, j;

    cin >> n;
    ck(n, 0, 100000);

    if (n == 0 or (n & 1)) {
        cout << "qiandaoshibai" << endl;
    } else {
        cout << "qiandaochenggong" << endl;
    }

    return 0;
}
