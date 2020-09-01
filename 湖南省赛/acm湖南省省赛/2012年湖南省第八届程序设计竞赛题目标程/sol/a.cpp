// Rujia Liu
#include<iostream>
using namespace std;

int main() {
  int T, x, y, z;
  cin >> T;
  while(T--) {
    cin >> x >> y >> z;
    cout << (2*x-y)*z/(x+y) << "\n";
  }
  return 0;
}
