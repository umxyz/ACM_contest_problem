#include "testlib.h"

using namespace std;
typedef long long LL;
int n;
vector<int> a;
const int MIN_V = 1;
const int MAX_V = 1000 * 1000 * 1000;
const int MAX_N = 5000;
int b[MAX_N];
bool is_power2(int x){
    return x && (x&(x-1))==0;
}
int read_output(InStream& ufo,TResult _res){
    int m = ufo.readInt(1,n);
    for(int i=0;i<m;i++){
        b[i]=ufo.readInt(MIN_V,MAX_V);
        if(!binary_search(a.begin(),a.end(),b[i])) quitf(_res, "the number didn't occur in a");
        for(int j=0;j<i;j++){
            if(b[j]==b[i]){
                quitf(_res, "there are at least two duplicated numbers");
            }
            if(is_power2(b[j]^b[i])){
                quitf(_res, "%d and %d differ in axactly one bit",b[j],b[i]);
            }
        }
    }
    return m;
}
int main(int argc, char * argv[])
{
    setName("checker of independent2");
    registerTestlibCmd(argc, argv);
    n = inf.readInt();
    a = inf.readInts(n,1,MAX_V);
    sort(a.begin(),a.end());
    int ans_res = read_output(ans, _fail);
    int ouf_res = read_output(ouf, _wa);
    if(ans_res != ouf_res) {
        if(ans_res > ouf_res)quitf(_wa,"author found better solution than user");
        else quitf(_fail, "user found better solution than author");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "Participant output contains extra tokens");
    }
    quitf(_ok, "complete the test");
}

