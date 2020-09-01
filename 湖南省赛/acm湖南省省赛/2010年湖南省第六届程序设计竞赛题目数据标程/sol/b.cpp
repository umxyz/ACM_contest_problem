#include<stdio.h>
int main() {
  char s[99];
  int a, b, c, n = 0;
  while(scanf("%s", &s) == 1) {
    if(sscanf(s, "%d+%d=%d", &a, &b, &c) == 3 && a+b==c) n++;
    if(sscanf(s, "%d-%d=%d", &a, &b, &c) == 3 && a-b==c) n++;
  }
  printf("%d\n", n);
  return 0;
}
