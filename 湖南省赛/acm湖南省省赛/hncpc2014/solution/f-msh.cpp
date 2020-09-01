#include<bits/stdc++.h>
using namespace std;
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define memo(a,v) memset(a,v,sizeof(a))
#define pb push_back
#define all(a) a.begin(),a.end()
#define eps (1e-9)
#define inf (1<<25)
#define i64 long long
#define u64 unsigned i64
#define MOD 1000000007

char a[22][22];
int num[22][22],mov[4][2] = {0,-1,-1,0,0,1,1,0},col[32],mask,n,m, k, ans, p;
bool mat[32][32];
void renumber(int x,int y,char ch,int cnt){
    num[x][y] = cnt;
    int i,nx,ny;
    for(i = 0;i<4;i++){
        nx = x + mov[i][0];
        ny = y + mov[i][1];
        if(nx<0 || ny<0 || nx>=n || ny>=m || num[nx][ny] != -1 || a[nx][ny]!=ch) continue;
        renumber(nx,ny,ch,cnt);
    }
}

int dfs(int u,int c,int flag){
    if(col[u]!=-1){
        if(col[u] != c) return 0;
        return 1;
    }
    p++;
    col[u] = c;
    for(int v = 0;v<k;v++){
        if(!mat[u][v] || ((mask & (1<<v))!=0) != flag ) continue;
        if(!dfs(v,1- c,flag))
            return 0;
    }
    return 1;
}
void recurse(int pos,int cnt){
    if(cnt>5) return;
    if(pos == k){
        if(cnt >= 2 && cnt<=k - 2){
            int cur1 = 1, cur2 = 1;
            memset(col,-1,sizeof(col));
            int flag1 = 0, flag2 = 0;
            for(int i = 0;i<k;i++){
                if(col[i]!=-1) continue;
                p = 0;
                if(mask & (1<<i)){
                    if(!dfs(i,0,1)){
                        cur1 = 0;
                        break;
                    }
                    cur1 *= 2;
                    if(p>1)
                        flag1 = 1;
                    continue;
                }
                if(!dfs(i,0,0)){
                    cur2 = 0;
                    break;
                }
                if(p>1)
                    flag2 = 1;
                cur2 *= 2;
            }
            if(!flag1)
                cur1-=2;
            if(!flag2)
                cur2-=2;
            cur1 = max(0,cur1);
            cur2 = max(0,cur2);
            ans += cur1*cur2;
        //    printf("%d %d\n",mask,cur1*cur2);
        }
        return;
    }
    mask |= (1<<pos);
    recurse(pos+1,cnt+1);
    mask ^= (1<<pos);
    recurse(pos+1,cnt);


}
int main(){
    double cl = clock();
    int i,j,x,y,l,cs = 1;
    while(scanf("%d %d",&n,&m) == 2){
        assert(1<=n && n<=20 && 1<=m && m<=20);
        for(i = 0;i<n;i++)
            scanf("%s",a[i]);
        memset(num,-1,sizeof(num));
        k = 0;
        for(i = 0;i<n;i++){
            for(j = 0;j<m;j++){
                assert('A'<=a[i][j] && a[i][j]<='Z');
                if(num[i][j]!=-1) continue;
                renumber(i,j,a[i][j],k++);
            }
        }
        memset(mat,0,sizeof(mat));
        for(i = 0;i<n;i++){
            for(j = 0;j<m;j++){
                for(l = 0;l<4;l++){
                    x = i + mov[l][0];
                    y = j + mov[l][1];
                    if(x<0 || x>=n || y<0 || y>=m || num[i][j] == num[x][y]) continue;
                    mat[num[i][j]][num[x][y]] = 1;
                }
            }
        }
        assert(1<=k && k<=30);
        ans = 0;
        mask = 0;
        recurse(0,0);
        printf("Case %d: %d\n",cs++, ans);
    }
    cl = clock() - cl;
    fprintf(stderr,"Run Time = %lf\n",cl/CLOCKS_PER_SEC);
	return 0;
}
