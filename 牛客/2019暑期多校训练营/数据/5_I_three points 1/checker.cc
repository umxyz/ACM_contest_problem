#include "testlib.h"

using namespace std;
typedef long long LL;
int w,h,a,b,c;
struct Point{
    double x, y;
    Point(double x=0, double y=0):x(x),y(y){}
    Point operator-(const Point _b)const{
        return Point(x-_b.x,y-_b.y);
    }
    double dis(){return sqrt(x*x+y*y);}
    void scan(InStream& ufo){
        x = ufo.readDouble();
        y = ufo.readDouble();
    }
}an[3];
const double EPS = 1e-6;
bool valid(){
    if(fabs((an[0]-an[1]).dis() - a) > EPS ||
       fabs((an[0]-an[2]).dis() - b) > EPS ||
       fabs((an[1]-an[2]).dis() - c) > EPS) return false;
    for(int i = 0; i < 3; i++) {
        if(an[i].x < -EPS || an[i].y < -EPS) return false;
        if(an[i].x > w + EPS) return false;
        if(an[i].y > h + EPS) return false;
    }
    return true;
}
int read_output(InStream& ufo,TResult _res,int cs){
    for(int i = 0; i < 3; i++) {
        an[i].scan(ufo);
    }
    if(!valid()) {
        quitf(_res, "the three points are invalid on test %d", cs);
    }
    return 1;
}
int main(int argc, char * argv[])
{
    setName("checker of three points 1");
    registerTestlibCmd(argc, argv);
    int T = inf.readInt();
    for(int cs = 1; cs <= T; cs++) {
        w = inf.readInt();
        h = inf.readInt();
        a = inf.readInt();
        b = inf.readInt();
        c = inf.readInt();
        int ans_res = read_output(ans, _fail, cs);
        int ouf_res = read_output(ouf, _wa, cs);
        if(ans_res != ouf_res) {
            if(ans_res == 1)quitf(_wa,"author found solution but user didn't on test %d", cs);
            else quitf(_fail, "user found solution but author didn't on test %d", cs);
        }
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "Participant output contains extra tokens");
    }
    quitf(_ok, "complete %d tests", T);
}

