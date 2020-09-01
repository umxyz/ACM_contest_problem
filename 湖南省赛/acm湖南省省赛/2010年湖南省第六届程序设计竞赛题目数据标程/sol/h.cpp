#include <cstdio>
#include <algorithm>
using namespace std;

#define X(A,B) (A[B[0]][B[1]][B[2]][B[3]][B[4]][B[5]])

double cache[7][7][7][7][7][7];
bool vis[7][7][7][7][7][7];

double win(int h[6])
{
  if (X(vis, h)) return X(cache, h);
  X(vis, h)=true;
  X(cache, h)=0.;

  int mx=0;
  for (int i=0; i < 6; i++) mx=max(mx, h[i]);

  int i=0, hh[6];
  for (int j=0; j < mx; j++){
    for (int d=0; d < 2; d++){
      i=0 + 5 * d;
      double loss=0.;
      for (int p=1; p <= 3; p++){
        for (int k=0; k < 6; k++) hh[k]=h[k];
        int pp=p;
        int k=i;
        while (pp){
          if (k < 0 || k > 5) break;
          if (hh[k] > j) hh[k]--, pp--;
          k+=1 - 2 * d;
        }
        loss+=win(hh);
      }
      loss=(1 - loss / 3.);
      if (loss > X(cache, h)) X(cache, h)=loss;
    }
  }
  return X(cache, h);
}

int main() {
  int n;
  while (scanf("%d", &n) == 1 && n) {
    int h[6]={0};
    for (int i=0; i < n; i++) scanf("%d", &h[i]);
    printf("%.6lf\n", win(h));
  }
  return 0;
}
