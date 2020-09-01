// Rujia Liu
#include<cstdio>
int main() {
  int x, y, kase = 0;
  while(scanf("%d%d", &x, &y) == 2) {
    int tot = 0;
    for(int a = x; a <= 1000 && a <= y; a++)
      for(int b = x; b <= 1000 && b <= y; b++) {
        int s = a*a*a + b*b*b;
        if(s % 10 != 3) continue;
        int c = s / 10;
        if(c >= x && c <= y) tot++;
      }
    printf("Case %d: %d\n", ++kase, tot);
  }
  return 0;
}
