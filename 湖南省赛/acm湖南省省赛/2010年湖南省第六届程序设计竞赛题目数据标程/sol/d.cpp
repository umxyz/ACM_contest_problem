#include<stdio.h>
#include<math.h>
int main() {
  double L, W, x, y, R, a, v, s;
  while(scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &L, &W, &x, &y, &R, &a, &v, &s) == 8) {
    if(!L) break;
    x -= R; y -= R; L -= R*2; W -= R*2; a *= acos(0.0)/90.0;
    double dx = fmod(fmod(v*s*cos(a), L*2)+L*2, L*2);
    double dy = fmod(fmod(v*s*sin(a), W*2)+W*2, W*2);
    if(x+dx <= L) x += dx; else if(x+dx <= L*2) x = L-(x+dx-L); else x = x+dx-L*2;
    if(y+dy <= W) y += dy; else if(y+dy <= W*2) y = W-(y+dy-W); else y = y+dy-W*2;
    printf("%.2lf %.2lf\n", x+R, y+R);
  }
  return 0;
}
