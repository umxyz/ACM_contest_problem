// Rujia Liu
#include<cmath>
#include<cstdio>
#include<iostream>

using namespace std;

const double PI = acos(-1.0);
const double TWO_PI = 2 * PI;
const double eps = 1e-6;

inline double NormalizeAngle(double rad, double center = PI) {
  return rad - TWO_PI * floor((rad + PI - center) / TWO_PI);
}

inline int dcmp(double x) {
  if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x),y(y) { }
};

typedef Point Vector;

inline Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x, A.y+B.y); }
inline Vector operator - (Point A, Point B) { return Vector(A.x-B.x, A.y-B.y); }

inline double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
inline double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }
inline double Length(Vector A) { return sqrt(Dot(A, A)); }

// 外接圆圆心。假定三点不共线
Point get_circumscribed_center(Point p1, Point p2, Point p3) {
  double bx = p2.x - p1.x;
  double by = p2.y - p1.y;
  double cx = p3.x - p1.x;
  double cy = p3.y - p1.y;
  double d = 2 * (bx * cy - by * cx);
  Point p;
  p.x = (cy * (bx * bx + by * by) - by * (cx * cx + cy * cy)) / d + p1.x;
  p.y = (bx * (cx * cx + cy * cy) - cx * (bx * bx + by * by)) / d + p1.y;
  return p;
}

double DistanceToArc(Point a, Point start, Point mid, Point end) {
  Point p = get_circumscribed_center(start, mid, end);
  bool CCW = dcmp(Cross(mid - start, end - start)) > 0;
  double ang_start = atan2(start.y-p.y, start.x-p.x);
  double ang_end = atan2(end.y-p.y, end.x-p.x);
  double r = Length(p - start);
  double ang = atan2(a.y-p.y, a.x-p.x);
  bool inside;
  if(CCW) {
    inside = NormalizeAngle(ang - ang_start) < NormalizeAngle(ang_end - ang_start);
  } else {
    inside = NormalizeAngle(ang - ang_end) < NormalizeAngle(ang_start - ang_end);
  }
  if(inside) {
    return fabs(r - Length(p - a));
  }
  return min(Length(a - start), Length(a - end));
}

int main() {
  int kase = 0;
  double x1, y1, x2, y2, x3, y3, xp, yp;
  while(cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> xp >> yp) {
    double ans = DistanceToArc(Point(xp,yp), Point(x1,y1), Point(x2,y2), Point(x3,y3));
    printf("Case %d: %.3lf\n", ++kase, ans);
  }
  return 0;
}
