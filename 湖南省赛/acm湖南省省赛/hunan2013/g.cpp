// Rujia Liu
#include<cstdio>
char name[100][5];

int main() {
  int n, q, p;
  scanf("%d", &n);
  for(int i = 0; i < n; i++) scanf("%s", name[i]);
  scanf("%d", &q);
  while(q--) {
    scanf("%d", &p); p--;
    if(name[p][0] != '?') printf("%s\n", name[p]);
    else for(int d = 1; ; d++) {
      bool b1 = (p-d >= 0 && name[p-d][0] != '?');
      bool b2 = (p+d < n && name[p+d][0] != '?');
      if(b1 && b2) { printf("middle of %s and %s\n", name[p-d], name[p+d]); break; }
      if(b1 || b2) {
        for(int i = 0; i < d; i++) printf("%s of ", b1 ? "right" : "left");
        printf("%s\n", b1 ? name[p-d] : name[p+d]);
        break;
      }
    }
  }
  return 0;
}
