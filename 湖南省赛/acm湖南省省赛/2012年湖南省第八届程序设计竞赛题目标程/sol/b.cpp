// Rujia Liu
#include<iostream>
#include<string>
using namespace std;

int main() {
  int T;
  cin >> T;
  while(T--) {
    int n, x = 0, d, p, cache[110];
    cin >> n;
    for(int i = 1; i <= n; i++) {
      string cmd;
      cin >> cmd;
      if(cmd == "LEFT") d = -1;
      else if(cmd == "RIGHT") d = 1;
      else {
        cin >> cmd >> p;
        d = cache[p];
      }
      cache[i] = d;
      x += d;
    }
    cout << x << "\n";
  }
  return 0;
}
