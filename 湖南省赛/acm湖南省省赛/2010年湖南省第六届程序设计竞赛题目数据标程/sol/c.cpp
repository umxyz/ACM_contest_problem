#include<stdio.h>
#include<string.h>
int main() {
  char s[200];
  while(scanf("%s", &s) == 1) {
    if(!strcmp(s, "0")) break;
    int m = 0;
    for(int i = 0; i < strlen(s); i++)
      m = (m*10+s[i]-'0')%17;
    printf("%d\n", m==0?1:0);
  }
  return 0;
}
