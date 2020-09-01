#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

typedef long long ll;
const int MAXN=1005;

struct Point
{
    ll x,y;
    Point(){}
    Point(ll _x,ll _y):x(_x),y(_y){}
    Point operator - (const Point &t)const
    {
        return Point(x-t.x,y-t.y);
    }
    ll operator * (const Point &t)const
    {
        return x*t.y-y*t.x;
    }
    bool operator == (const Point &t)const
    {
        return x==t.x && y==t.y;
    }
}p[MAXN],q[2],pp[10005][MAXN];
int nn[10005];

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int T=inf.readInt(1, 10000, "T");//inf.readEoln();
    for (int ca=1;ca<=T;ca++){
    	nn[ca] = inf.readInt(1, 1000, "n");
		//inf.readEoln();
    	for (int i=0;i<nn[ca];i++){
			pp[ca][i].x=inf.readInt(-1000, 1000, "x_i");
			//inf.readSpace();
			pp[ca][i].y=inf.readInt(-1000, 1000, "y_i");
			//inf.readEoln();
		}
	}
    for(int ca=1;ca<=T;ca++)
    {
        int n=nn[ca];
        for(int i=0;i<n;i++)
            p[i]=pp[ca][i];
        
		q[0].x=ouf.readInt(-1000000000, 1000000000, "x_i out of range");
		//ouf.readSpace();
		q[0].y=ouf.readInt(-1000000000, 1000000000, "y_i out of range");
		//ouf.readSpace();
		q[1].x=ouf.readInt(-1000000000, 1000000000, "x_i out of range");
		//ouf.readSpace();
		q[1].y=ouf.readInt(-1000000000, 1000000000, "y_i out of range");
		//ouf.readEoln();
		if (q[0]==q[1])
			quitf(_wa, "In case %d, two input points of the d-th line are coincide.\n", ca);

		int A=0,B=0;
        for(int i=0;i<n;i++)
        {
            int j=0;
            ll t=(p[i]-q[j<<1])*(q[j<<1|1]-q[j<<1]);
            if(t==0)
                quitf(_wa, "In case %d, there exists a line passing through some given points.\n", ca);
			if (t<0) A++;else B++;
        }
        if (A!=B)
			quitf(_wa, "In case %d, the number in each part(%d, %d) is not equal.\n", ca, A, B);
    }
    quitf(_ok, "%d cases", T);
}
