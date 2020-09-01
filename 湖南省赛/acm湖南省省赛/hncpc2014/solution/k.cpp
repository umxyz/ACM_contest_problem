// Rujia Liu
#include<cstdio>

int kase = 0, s1, s2;
double p[10];
long long cnt, tot;

bool read() {
  for(int i = 0; i < 10; i++) {
    if(scanf("%lf", &p[i]) != 1) return false;
  }
  if(scanf("%d-%d", &s1, &s2) == 2);
}

int left(int k, int team) {
  int v = k / 2;
  if(team == 0 && k % 2 == 1) v++;
  return 5 - v;
}

// kick k, current score a-b
double dfs(int k, int a, int b) {
  if(k == 10 || a+left(k,0) < b || b+left(k,1) < a) return (a == s1 && b == s2 ? 1 : 0);
  double ans = 0;
  int idx = k/2;
  if(k % 2 == 0) {
    ans += (1-p[idx])*dfs(k+1, a, b);
    ans += p[idx]*dfs(k+1, a+1, b);
  }
  else {
    idx += 5;
    ans += (1-p[idx])*dfs(k+1, a, b);
    ans += p[idx]*dfs(k+1, a, b+1);
  }
  return ans;
}

void solve() {
  cnt = tot = 0;
  double ans = dfs(0, 0, 0);
  printf("Case %d: %.2lf%%\n", ++kase, (double)(ans*100));
}

int main() {
  while(read()) solve();
  return 0;
}
