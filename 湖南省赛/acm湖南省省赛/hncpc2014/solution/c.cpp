// Rujia Liu
#include<cstdio>
#include<string>
#include<string.h>
#include<algorithm>
#include<cassert>
using namespace std;

bool cool(string w) {
  int cnt[26] = {0};
  if(w.length() < 2) return false;
  for(int i = 0; i < w.length(); i++)
    cnt[w[i]-'a']++;
  sort(cnt, cnt+26);
  for(int i = 1; i < 26; i++)
    if(cnt[i] != 0 && cnt[i] == cnt[i-1]) return false;
  return true;
}

int main() {
  int n, kase = 0;
  while(scanf("%d", &n) == 1) {
    assert(n<=10000);
    int cnt = 0;
    for(int i = 0; i < n; i++) {
      char w[100];
      scanf("%s", w);
      assert(strlen(w) <= 30);
      if(cool(w)) cnt++;
//      if(cool(w)) printf("%s\n", w);
    }
    printf("Case %d: %d\n", ++kase, cnt);
  }
  return 0;
}
