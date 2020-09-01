#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
#define sqr(x) ((x)*(x))

const double eps=1e-6;
const double inf=8;

const double pi=3.14159265358979323846;

inline bool cmpDouble(const double &a,const double &b)
{return fabs(a-b)<eps;}
struct Tpoint
{
	double x,y;
	Tpoint(){}
	Tpoint(double a,double b){x=a;y=b;}
	inline double norm(){ return sqrt( sqr(x)+sqr(y) ); }
};

inline Tpoint operator +(const Tpoint &a,const Tpoint &b){return Tpoint(a.x+b.x,a.y+b.y);}
inline Tpoint operator -(const Tpoint &a,const Tpoint &b){return Tpoint(a.x-b.x,a.y-b.y);}
inline Tpoint operator *(const double &a,const Tpoint &b){return Tpoint(a*b.x,a*b.y);}
inline Tpoint operator *(const Tpoint &b,const double &a){return Tpoint(a*b.x,a*b.y);}
inline Tpoint operator /(const Tpoint &a,const double &b){return Tpoint(a.x/b,a.y/b);}
inline bool operator <(const Tpoint &a,const Tpoint &b){return a.x+eps<b.x || fabs(a.x-b.x)<eps && a.y+eps<b.y;}
inline bool operator ==(const Tpoint &a,const Tpoint &b){return fabs(a.x-b.x)<eps && fabs(a.y-b.y)<eps;}
inline double det(const Tpoint &a,const Tpoint &b){return a.x*b.y-a.y*b.x;}
inline double dot(const Tpoint &a,const Tpoint &b){return a.x*b.x+a.y*b.y;}

struct P3
{
	double x,y,z;
	
	P3(){}
	P3(double a,double b,double c){x=a;y=b;z=c;}
	inline void read(){scanf("%lf%lf%lf",&x,&y,&z);}
};
inline P3 operator +(const P3 &a,const P3 &b){return P3(a.x+b.x,a.y+b.y,a.z+b.z);}
inline P3 operator -(const P3 &a,const P3 &b){return P3(a.x-b.x,a.y-b.y,a.z-b.z);}
inline P3 operator *(const double &a,const P3 &b){return P3(a*b.x,a*b.y,a*b.z);}
inline P3 operator *(const P3 &b,const double &a){return P3(a*b.x,a*b.y,a*b.z);}
inline P3 operator /(const P3 &a,const double &b){return P3(a.x/b,a.y/b,a.z/b);}

struct Tcir
{
	double r;
	Tpoint o;
	
	Tcir(){}
	Tcir(Tpoint x,double y){o=x,r=y;}
};
vector <Tcir> Circle;
typedef vector <Tpoint> TP;
vector <TP> Poly;

struct Tinter
{
	double x,y,Area,mid;
	int delta;
	Tinter(){}
	Tinter(double xx,double yy,double mm,int dd,double aa)
	{
		x=xx;y=yy;mid=mm;
		delta=dd;Area=aa;
	}
};
inline bool operator <(const Tinter &a,const Tinter &b){return a.mid>b.mid+eps;}
inline bool operator ==(const Tinter &a,const Tinter &b){return fabs(a.mid-b.mid)<eps;}
vector <Tinter> inter;
vector <double> bak;

inline double dist(const Tpoint &a,const Tpoint &b)
{
	return sqr(a.x-b.x)+sqr(a.y-b.y);
}

inline void Add(double x)
{
	bak.push_back(x);
}

inline void CircleIntersectCircle(const Tcir &a,const Tcir &b)
{
	double l=dist(a.o,b.o);
	double s=((a.r-b.r)*(a.r+b.r)/l+1)/2;
	double t=sqrt(-(l-sqr(a.r+b.r))*(l-sqr(a.r-b.r))/(l*l*4));
	double ux=b.o.x-a.o.x,uy=b.o.y-a.o.y;
	double ix=a.o.x+s*ux+t*uy,iy=a.o.y+s*uy-t*ux;
	double jx=a.o.x+s*ux-t*uy,jy=a.o.y+s*uy+t*ux;
	Add(ix);
	Add(jx);
}

inline bool InLine(const Tpoint &a,const Tpoint &b,const Tpoint &c)
{
	return fabs(det(b-a,c-a))<eps && dot(a-c,b-c)<eps;
}

inline void LineToLine(const Tpoint &a,const Tpoint &b,const Tpoint &c,const Tpoint &d)
{
	double s1=det(c-a,b-a),s2=det(b-a,d-a);
	if (s1*s2<-eps) return;
	Tpoint e=c+(d-c)*s1/(s1+s2);
	
	if (InLine(a,b,e) && InLine(c,d,e))
	{
		Add(e.x);
	}
}

inline void LineToCircle(const Tpoint &a,const Tpoint &b,const Tcir &c)
{
	double h=fabs(det(c.o-a,b-a))/(b-a).norm();
	if (h>c.r+eps) return;
	double lamda=dot(c.o-a,b-a);
	lamda/=dist(a,b);
	Tpoint x=a+(b-a)*lamda;
	double d=sqrt( sqr(c.r)-sqr(h) );
	d/=(b-a).norm();
	Tpoint e=x+(b-a)*d;
	Tpoint f=x-(b-a)*d;
	if (InLine(a,b,e))
		Add(e.x);
	if (InLine(a,b,f))
		Add(f.x);
	return;
}

inline void CircleToCircle()
{
	for (int i=0;i<Circle.size();++i)
	{
		Add(Circle[i].o.x-Circle[i].r);
		Add(Circle[i].o.x+Circle[i].r);
		Add(Circle[i].o.x);
		for (int j=i+1;j<Circle.size();++j)
		if (dist(Circle[i].o,Circle[j].o)<=sqr(Circle[i].r+Circle[j].r))
		if (dist(Circle[i].o,Circle[j].o)>=sqr(Circle[i].r-Circle[j].r))
			CircleIntersectCircle(Circle[i],Circle[j]);
	}
}

inline void CircleToPoly()
{
	for (int i=0;i<Circle.size();++i)
		for (int j=0;j<Poly.size();++j)
			for (int v=0;v<Poly[j].size();++v)
				LineToCircle(Poly[j][v],Poly[j][(v+1)%Poly[j].size()],Circle[i]);
}

inline void PolyToPoly()
{
	for (int i=0;i<Poly.size();++i)
		for (int u=0;u<Poly[i].size();++u)
			Add(Poly[i][u].x);
	for (int i=0;i<Poly.size();++i)
		for (int j=i+1;j<Poly.size();++j)
			for (int u=0;u<Poly[i].size();++u)
				for (int v=0;v<Poly[j].size();++v)
					LineToLine(Poly[i][u],Poly[i][(u+1)%Poly[i].size()],Poly[j][v],Poly[j][(v+1)%Poly[j].size()]);
}

inline void Get(const Tcir &c,double x,double &l,double &r)
{
	double y=fabs(c.o.x-x);
	double d=sqrt(fabs( sqr(c.r)-sqr(y) ));
	l=c.o.y+d;
	r=c.o.y-d;
}

inline double arcArea(const Tcir &a,double l,double x,double r,double y)
{
	double len=sqrt(sqr(l-r) + sqr(x-y));
	double d=sqrt(sqr(a.r)-sqr(len)/4.0);
	double angle=atan(len/2.0/d);
	return fabs(angle*sqr(a.r)-d*len/2.0);
}

inline void Get_Interval(const Tcir &a,double l,double r)
{
	double L1,L2,R1,R2,M1,M2;
	Get(a,l,L1,L2);
	Get(a,r,R1,R2);
	Get(a,(l+r)/2.0,M1,M2);
	int D1=1,D2=-1;
	double A1=arcArea(a,l,L1,r,R1),A2=arcArea(a,l,L2,r,R2);
	inter.push_back( Tinter(L1,R1,M1,D1,A1) );
	inter.push_back( Tinter(L2,R2,M2,D2,A2) );
}

inline double calcSlice(double xl,double xr)
{
	inter.clear();
	double lmost=-inf,rmost=inf;
	for (int i=0;i<Poly.size();++i)
	{
		int cc=0;
		Tinter I[5];
		for (int u=0;u<Poly[i].size();++u)
		{
			Tpoint x=Poly[i][u];
			Tpoint y=Poly[i][(u+1)%Poly[i].size()];
			double l=min(x.x,y.x),r=max(x.x,y.x);
			if (l<=xl+eps && xr<=r+eps)
			{
				if (fabs(l-r)<eps) continue;
				Tpoint d=y-x;
				Tpoint Left=x+d/d.x*(xl-x.x);
				Tpoint Right=x+d/d.x*(xr-x.x);
				Tpoint Mid=(Left+Right)/2;
				I[cc++]=Tinter(Left.y,Right.y,Mid.y,1,0);
			}
		}
		sort(I,I+cc);
		if (cc==2)
		{
			I[1].delta=-1;
			inter.push_back(I[0]);
			inter.push_back(I[1]);
			lmost=max(lmost,I[1].mid);
			rmost=min(rmost,I[0].mid);
		}
	}
	
	for (int i=0;i<Circle.size();++i)
	if (fabs(Circle[i].o.x-xl)<Circle[i].r+eps && fabs(Circle[i].o.x-xr)<Circle[i].r+eps)
		Get_Interval(Circle[i],xl,xr);
	
	if (!inter.size()) return 0;
	double ans=0;
	sort(inter.begin(),inter.end());
	int cnt=0;
	for (int i=0;i<inter.size();++i)
	{
		if (cnt>0)
		{
			ans+=(fabs(inter[i-1].x-inter[i].x)+fabs(inter[i-1].y-inter[i].y))*(xr-xl)/2.0;
			ans+=inter[i-1].delta*inter[i-1].Area;
			ans-=inter[i].delta*inter[i].Area;
		}
		cnt+=inter[i].delta;
	}
	return ans;
}

#define maxn 105
int n,m;
struct Poly4
{
	P3 p[4];
}a[maxn];
struct Sphere
{
	P3 o;
	double r;
	inline void read(){o.read();scanf("%lf",&r);}
}b[maxn];

inline bool equal(double a,double b)
{
	return fabs(a-b)<eps;
}

inline bool InterSect(const Tpoint &a,const Tpoint &b,const Tpoint &c,const Tpoint &d)
{
	double s1=det(b-a,c-a),s2=det(b-a,d-a);
	if (s1*s2>-eps) return false;
	s1=det(d-c,a-c),s2=det(d-c,b-c);
	if (s1*s2>-eps) return false;
	return true;
}

inline void ToHull(vector <Tpoint> &a)
{
	sort(a.begin(),a.end());
	int hull[10],len,limit=1;
	hull[len=1]=0;
	for (int i=1;i<4;++i)
	{
		while (len>limit && det(a[hull[len]]-a[hull[len-1]],a[i]-a[hull[len]])>=0) --len;
		hull[++len]=i;
	}
	limit=len;
	for (int i=2;i>=0;--i)
	{
		while (len>limit && det(a[hull[len]]-a[hull[len-1]],a[i]-a[hull[len]])>=0) --len;
		hull[++len]=i;
	}
	vector <Tpoint> b=a;
	a.resize(len-1);
	for (int i=0;i<len-1;++i)
		a[i]=b[hull[i+1]];
}

inline double calcArea(double z)
{
	Poly.clear();
	Circle.clear();
	bak.clear();
	for (int i=0;i<n;++i)
	{
		vector <Tpoint> cross;
		for (int j=0;j<4;++j)
			for (int k=j+1;k<4;++k)
			if (!equal(a[i].p[j].z,a[i].p[k].z))
			{
				double l=min(a[i].p[j].z,a[i].p[k].z),r=max(a[i].p[j].z,a[i].p[k].z);
				if (l<=z+eps && z<=r+eps)
				{
					P3 d=a[i].p[k]-a[i].p[j];
					d=d/d.z;
					d=d*(z-a[i].p[j].z);
					d=d+a[i].p[j];
					Tpoint x(d.x,d.y);
					cross.push_back(x);
				}
			}
		sort(cross.begin(),cross.end());
		cross.erase(unique(cross.begin(),cross.end()),cross.end()); 
		if (cross.size()>2)
		{
			if (cross.size()>4){puts("Too Many Points!!!");while (1);}
			if (cross.size()==4)
				ToHull(cross);
			Poly.push_back(cross);
		}
	}
	
	for (int i=0;i<m;++i)
	if (fabs(z-b[i].o.z)+eps<b[i].r)
	{
		Tpoint o(b[i].o.x,b[i].o.y);
		double r=sqrt( sqr(b[i].r)-sqr(z-b[i].o.z) );
		Circle.push_back(Tcir(o,r));
	}
	
	CircleToCircle();
	CircleToPoly();
	PolyToPoly();
    
	sort(bak.begin(),bak.end());
	double res=0;
	for (int i=0;i+1<bak.size();++i)
	if (fabs(bak[i+1]-bak[i])>eps)
		res+=calcSlice(bak[i],bak[i+1]);
	return res;
}

int main()
{
	for (;scanf("%d%d",&n,&m)!=EOF && (n+m);)
	{
		for (int i=0;i<n;++i)
			for (int j=0;j<4;++j)
				a[i].p[j].read();
		
		for (int i=0;i<m;++i)
			b[i].read();
		
		double last=0,Ans=calcArea(-inf)+calcArea(inf);
		const int Block=4000;
		double h=(inf+inf)/(double)Block;
		for (int i=1;i<Block;i+=2)
			Ans+=4*calcArea(-inf+i*h);
		for (int i=2;i<Block;i+=2)
			Ans+=2*calcArea(-inf+i*h);
		Ans=Ans*h/3.0;
		printf("%.3f\n",Ans);
	}
	return 0;
}
