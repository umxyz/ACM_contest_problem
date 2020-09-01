// Rujia Liu
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const double eps = 1e-8;
int dcmp(double x) {
  if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

struct Point3 {
  double x, y, z;
  Point3(double x=0, double y=0, double z=0):x(x),y(y),z(z) { }
};

typedef Point3 Vector3;

Vector3 operator + (Vector3 A, Vector3 B) {
  return Vector3(A.x+B.x, A.y+B.y, A.z+B.z);
}

Vector3 operator - (Point3 A, Point3 B) {
  return Vector3(A.x-B.x, A.y-B.y, A.z-B.z);
}

Vector3 operator * (Vector3 A, double p) {
  return Vector3(A.x*p, A.y*p, A.z*p);
}

Vector3 operator / (Vector3 A, double p) {
  return Vector3(A.x/p, A.y/p, A.z/p);
}

bool operator < (const Point3& a, const Point3& b) {
  if(dcmp(a.x - b.x) != 0) return a.x < b.x;
  if(dcmp(a.y - b.y) != 0) return a.y < b.y;
  if(dcmp(a.z - b.z) != 0) return a.z < b.z;
  return false;
}

bool operator == (const Point3& a, const Point3& b) {
  return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0 && dcmp(a.z-b.z) == 0;
}

Point3 read_point3() {
  Point3 p;
  scanf("%lf%lf%lf", &p.x, &p.y, &p.z);
  return p;
}

double Dot(Vector3 A, Vector3 B) { return A.x*B.x + A.y*B.y + A.z*B.z; }
double Length(Vector3 A) { return sqrt(Dot(A, A)); }
double Angle(Vector3 A, Vector3 B) { return acos(Dot(A, B) / Length(A) / Length(B)); }
Vector3 Cross(Vector3 A, Vector3 B) { return Vector3(A.y*B.z - A.z*B.y, A.z*B.x - A.x*B.z, A.x*B.y - A.y*B.x); }
double Area2(Point3 A, Point3 B, Point3 C) { return Length(Cross(B-A, C-A)); }
double Volume6(Point3 A, Point3 B, Point3 C, Point3 D) { return Dot(D-A, Cross(B-A, C-A)); }

#include<cstdlib>
#include<cstring>
#include<queue>
using namespace std;

double rand01() { return rand() / (double)RAND_MAX; }
double randeps() { return (rand01() - 0.5) * eps; }

Point3 add_noise(Point3 p) {
  return Point3(p.x + randeps(), p.y + randeps(), p.z + randeps());
}

const int maxn = 2000 + 10;
int vis[maxn][maxn];

struct Face{
  int v[3];
  Vector3 normal(Point3 *P) const {
    return Cross(P[v[1]]-P[v[0]], P[v[2]]-P[v[0]]);
  }
  int cansee(Point3* P, int i) const {
    return Dot(P[i]-P[v[0]], normal(P)) > 0 ? 1 : 0;
  }
  double Area2(Point3* P) const {
    return ::Area2(P[v[0]], P[v[1]], P[v[2]]);
  }
  double Volume6(Point3* P, const Point3& C) const {
    return ::Volume6(P[v[0]], P[v[1]], P[v[2]], C);
  }
  double distance(Point3* P, const Point3& C) const {
    return -Volume6(P, C) / Area2(P);
  }
  Point3 centroid(Point3* P, const Point3& C) const {
   return (C+P[v[0]]+P[v[1]]+P[v[2]])/4.0;
  }
};

// 增量法求三维凸包。
// 注意：没有考虑各种特殊情况（如四点共面）。实践中，请在调用前对输入点进行微小扰动
vector<Face> CH3D(Point3* P, int n) {
  vector<Face> cur;
  // 由于已经进行扰动，前三个点不共线
  cur.push_back((Face){{0, 1, 2}});
  cur.push_back((Face){{2, 1, 0}});
  for(int i = 3; i < n; i++) {
    vector<Face> next;
    // 计算每条边的“左面”的可见性
    for(int j = 0; j < cur.size(); j++) {
      Face& f = cur[j];
      int res = f.cansee(P, i);
      if(!res) next.push_back(f);
      for(int k = 0; k < 3; k++) vis[f.v[k]][f.v[(k+1)%3]] = res;
    }
    for(int j = 0; j < cur.size(); j++)
      for(int k = 0; k < 3; k++) {
        int a = cur[j].v[k], b = cur[j].v[(k+1)%3];
        if(vis[a][b] != vis[b][a] && vis[a][b]) // (a,b)是分界线，左边对P[i]可见
          next.push_back((Face){{a, b, i}});
      }
    cur = next;
  }
  return cur;
}

// 点在三角形P0, P1, P2中
bool PointInTri(Point3 P, Point3 P0, Point3 P1, Point3 P2) {
  double area1 = Area2(P, P0, P1);
  double area2 = Area2(P, P1, P2);
  double area3 = Area2(P, P2, P0);
  return dcmp(area1 + area2 + area3 - Area2(P0, P1, P2)) == 0;
}

// 三角形P0P1P2是否和线段AB相交
bool TriSegIntersection(Point3 P0, Point3 P1, Point3 P2, Point3 A, Point3 B, Point3& P) {
  Vector3 n = Cross(P1-P0, P2-P0);
  Point3 C = B-A;
  if(dcmp(Dot(n, B-A)) == 0) return false; // 线段A-B和平面P0P1P2平行或共面
  else { // 平面A和直线P1-P2有惟一交点
    double t = Dot(n, P0-A) / Dot(n, B-A);
    if(dcmp(t) < 0 || dcmp(t-1) > 0) return false; // 不在线段AB上
    P = A + (B-A)*t; // 交点
    return PointInTri(P, P0, P1, P2);
  }
}

struct ConvexPolyhedron {
  int n;
  Point3 P[maxn], P2[maxn];
  vector<Face> faces;

  ConvexPolyhedron() {
    n = 0;
  }

  void copy_from(const ConvexPolyhedron& other) {
    n = other.n;
    for(int i = 0; i < n; i++) { P[i] = other.P[i]; P2[i] = other.P2[i]; }
    faces = other.faces;
  }

  void build() {
    sort(P, P+n);
    n = unique(P, P+n) - P;
    for(int i = 0; i < n; i++) P2[i] = add_noise(P[i]);
    faces.clear();
    if(n >= 4) faces = CH3D(P2, n);
  }

  double volume() {
    if(n < 4) return 0.0;
    double res = 0;
    for(int i = 0; i < faces.size(); i++)
      res += faces[i].Volume6(P, P[0]);
    return -res / 6.0;
  }

  bool is_inside(const Point3& p) {
    if(n < 4) return false;
    for(int i = 0; i < faces.size(); i++)
      if(dcmp(faces[i].Volume6(P, p)) > 0) return false;
    return true;
  }

  void intersect(ConvexPolyhedron& other) {
    Point3 inter[maxn];
    Point3 T1[3], T2[3], PP;

    // get intersections
    int c = 0;
    for(int f1 = 0; f1 < faces.size(); f1++) {
      for(int i = 0; i < 3; i++) T1[i] = P2[faces[f1].v[i]];
      for(int f2 = 0; f2 < other.faces.size(); f2++) {
        for(int i = 0; i < 3; i++) T2[i] = other.P2[other.faces[f2].v[i]];
        for(int i = 0; i < 3; i++) {
          if(TriSegIntersection(T1[0], T1[1], T1[2], T2[i], T2[(i+1)%3], PP)) inter[c++] = PP;
          if(TriSegIntersection(T2[0], T2[1], T2[2], T1[i], T1[(i+1)%3], PP)) inter[c++] = PP;
        }
      }
    }

    for(int i = 0; i < n; i++)
      if(other.is_inside(P[i])) inter[c++] = P[i];
    for(int i = 0; i < other.n; i++)
      if(is_inside(other.P[i])) inter[c++] = other.P[i];

    if(c) {
      sort(inter, inter+c);
      c = unique(inter, inter+c) - inter;
    }

    // rebuild
    n = c;
    for(int i = 0; i < n; i++) P[i] = inter[i];
    build();
  }
};

#include<cassert>
const int maxt = 10;
int n, k, m;
ConvexPolyhedron CH[maxt];

double intersectS(int S) {
  ConvexPolyhedron res;
  int i;
  for(i = 0; i < n; i++) if(S & (1<<i)) {
    res.copy_from(CH[i]);
    break;
  }
  for(i++; i < n; i++) if(S & (1<<i))
    res.intersect(CH[i]);
  return res.volume();
}

int C(int n, int m) {
  int ans = 1;
  for(int i = 0; i < m; i++) ans *= n-i;
  for(int i = 1; i <= m; i++) ans /= i;
  return ans;
}

double volumeK(int k) {
  double ans = 0.0;
  for(int S = 0; S < (1<<n); S++) {
    int c = 0;
    for(int i = 0; i < n; i++) if(S & (1<<i)) c++;
    if(c < k) continue;
    double vol = intersectS(S);
    if((c - k) % 2 == 1) ans -= vol * C(c,k); else ans += vol * C(c,k);
  }
  return ans;
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%d%d%d", &n, &k, &m);
    for(int i = 0; i < n; i++) CH[i].n = 0;
    for(int i = 0; i < m; i++) {
      int t;
      double x, y, z;
      scanf("%d%lf%lf%lf", &t, &x, &y, &z); t--;
      CH[t].P[CH[t].n++] = Point3(x, y, z);
    }
    for(int i = 0; i < n; i++) {
      int n2 = CH[i].n;
      CH[i].build();
      assert(n2 == CH[i].n);
    }

    double ans = 0.0;
    for(int i = k; i <= n; i++) ans += volumeK(i);
    printf("%.5lf\n", ans);
  }
  return 0;
}
