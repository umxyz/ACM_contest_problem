#include<cstdio>
#include<ctime>
#include<iostream>
#include<cstring>
using namespace std;

const int MAXN = 2010;
int n, m, v[MAXN], u[MAXN], ans;
struct Trie {
	int cnt, ch[1010*1010*29][2];
	inline void insert(int x) {
		int i, p = 1;
		for(i = 28; i >= 0; i--) {
			bool c = (x>>i)&1;
			if(!ch[p][c]) ch[p][c] = ++cnt;
			p = ch[p][c];
		}
	}
	inline int Query(int x) {
		int p = 1, res = 0, i;
		for(i = 28; i >= 0; i--) {
			bool c = (x>>i)&1;
			if(ch[p][c^1]) {
				p = ch[p][c^1];
				res = res<<1|1;
			}
			else {
				p = ch[p][c];
				res = res<<1;
			}
		}
		return res;
	}
}T;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	for(; !isdigit(ch); ch = getchar()) if(ch=='-') f=-1;
	for(; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch^48);
	return x * f;
}

inline int max(int a, int b) {
	return a > b ? a : b;
}

inline int min(int a, int b) {
	return a < b ? a : b;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
#endif
	int i, j, l;
	n = read(), m = read();
	for(i = 1; i <= n; i++) v[i] = read();
	for(i = 1; i <= m; i++) u[i] = read();
	for(i = 1; i <= n; i++) {
		int res = 0;
		for(j = i+1; j <= n; ++++j) {
			res = res^v[j-1]^v[j];
			ans = max(ans, res);
		}
	}
	for(i = 1; i <= m; i++) {
		int res = 0;
		for(j = i+1; j <= m; ++++j) {
			res = res^u[j-1]^u[j];
			ans = max(ans, res);
		}
	}
	for(i = 2; i <= n; i++) v[i] = v[i]^v[i-1];
	for(i = 2; i <= m; i++) u[i] = u[i]^u[i-1];
	cerr << clock() << endl;
	T.cnt = 1;
	for(l = 1; l <= n; ++++l) {
		int e = n-l+1;
		for(i = 1; i <= e; i++) T.insert(v[i+l-1]^v[i-1]);
	}
	for(l = 1; l <= m; ++++l) {
		int e = m-l+1;
		for(i = 1; i <= e; i++) 
			ans = max(ans, T.Query(u[i+l-1]^u[i-1]));
	}
	printf("%d\n", ans);
	cerr << clock() << endl;
	return 0;
}
