#include<stdio.h>
int main() {
  int n;
  int cf[20];
  while(scanf("%d", &n) == 1) {
    if(!n) break;
    for(int i = 0; i <= n; i++) scanf("%d", &cf[i]);
    double l = -1.0, r = 1e6, m;
    for(int i = 0; i < 100; i++) {
      m = l + (r-l)/2;
      double f = 1.0, s = 0;
      for(int j = 1; j <= n; j++) {
        f /= (1+m);
        s += cf[j]*f;
      }
      if(s < -cf[0]) r = m; else l = m;
    }
    printf("%.2lf\n", m);
  }
  return 0;
}
