// Rujia Liu
#include<cstdio>
int n;
char s[6][50];

int main() {
  scanf("%d", &n);
  for(int i = 0; i < 6; i++) scanf("%s", s[i]);
  for(int i = 0; i < n; i++) {
    int ans = 1;
    if(s[3][i*4] == '*') ans = 2;
    else if(s[3][i*4+2] == '*') ans = 3;
    printf("%d", ans);
  }
  printf("\n");
  return 0;
}
