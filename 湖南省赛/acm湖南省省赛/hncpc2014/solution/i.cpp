// Rujia Liu
#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;

#define dist(a,b) (max(abs(r[a]-r[b]),abs(c[a]-c[b])))

int main() {
  int r[3], c[3], kase = 0;
  while(cin>>r[0]>>c[0]>>r[1]>>c[1]>>r[2]>>c[2]) {
    int dr = abs(r[0]-r[1]);
    int dc = abs(c[0]-c[1]);
    int d = max(dr, dc);
    if(dr == dc && dist(0,1) == dist(0,2) + dist(2,1)) d++;
    printf("Case %d: %d\n", ++kase, d);
  }
  return 0;
}
