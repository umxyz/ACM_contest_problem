// Rujia Liu
#include<cstdio>
#include<cstring>
#include<cctype>
const int maxn = 1000 + 5;
int n, k, best, bestL;
char s[maxn];

void expand(int L, int R, int diff) {
  if(diff > k) return;
  for(;;) {
    int len = R-L+1;
    if(len > best || (len == best && L < bestL)) { best = len; bestL = L; }
    do { L--; } while(L >= 0 && !isalpha(s[L]));
    do { R++; } while(R < n && !isalpha(s[R]));
    if(L < 0 || R >= n) return;
    if(tolower(s[L]) != tolower(s[R])) diff++;
    if(diff > k) return;
  }
}

int main() {
  int kase = 0;
  while(scanf("%d\n", &k) == 1) {
    fgets(s, maxn, stdin);
    n = strlen(s);
    if(s[n-1] == '\n') n--;
    best = bestL = 0;
    for(int i = 0; i < n; i++) {
      int L = i, R = i, diff = 0;
      expand(L, R, 0);
      do { R++; } while(R < n && !isalpha(s[R]));
      if(R >= n) continue;
      if(tolower(s[L]) != tolower(s[R])) diff++;
      expand(L, R, diff);
    }
    printf("Case %d: %d %d\n", ++kase, best, bestL+1);
  }
  return 0;
}
