#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

const int MAXN = 110;
int n, a[MAXN], ans;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	for(; !isdigit(ch); ch = getchar()) if(ch=='-') f=-1;
	for(; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch^48);
	return x * f;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
#endif
	int i, j, T = read();
	while(T--) {
		ans = 0;
		n = read();
		for(i = 1; i <= n; i++) a[i] = read();
		for(i = 1; i <= n; i++) 
			for(j = i+1; j <= n; j++) if(a[i] < a[j]) ans++;
		if(ans & 1) printf("Q\n");
		else printf("T\n");
	}
	return 0;
}
