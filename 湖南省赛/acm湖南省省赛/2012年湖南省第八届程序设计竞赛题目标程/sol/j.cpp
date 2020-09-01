// Rujia Liu
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

const int maxn = 1000 + 10;
int n, m, A[maxn], B[maxn], last[maxn], d[maxn][maxn], f[maxn][maxn];

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &A[i]);
    scanf("%d", &m);
    for(int i = 0; i < m; i++) scanf("%d", &B[i]);

    for(int j = 0; j < m; j++) {
      last[j] = -1;
      for(int k = 0; k < j; k++) if(B[k] == B[j]) last[j] = max(last[j], k);
    }

    int ans = 0;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++) {
        d[i][j] = 0;
        if(A[i] == B[j]) {
          d[i][j] = 1;
          if(last[j] >= 0) d[i][j] = max(1, d[i][last[j]]);
          if(i > 0)
            for(int k = last[j]+1; k < j; k++)
              if(B[k] < B[j]) d[i][j] = max(d[i][j], f[i-1][k] + 1);
        }
        f[i][j] = d[i][j];
        if(i > 0) f[i][j] = max(f[i-1][j], f[i][j]);
        ans = max(ans, d[i][j]);
      }

    printf("%d\n", ans);
  }
  return 0;
}
