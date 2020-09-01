#include "testlib.h"

using namespace std;
typedef long long LL;
int n;
const int MAX_M = 5;
const int MAX_LEN = 10000;
int read_output(InStream& ufo,TResult _res){
    string s = ufo.readString();
    if(s=="Impossible")return -1;
    if(s.size()>MAX_LEN) quitf(_res, "the number of digit must be <= 10,000");
    if(s.size() == 0) quitf(_res, "the string cannot be empty");
    int v=0,v2=0;
    for(int i=0;i<(int)s.size();i++){
        if(!i){
            if(s[i]<'1'||s[i]>'9') quitf(_res, "output must be an postive integer");
        }
        else{
            if(s[i]<'0'||s[i]>'9') quitf(_res, "output must be an postive integer");
        }
        v2+=s[i]-'0';
        v2%=n;
        v*=10;
        v+=s[i]-'0';
        v%=n;
    }
    if(v) quitf(_res, "output must be divided by n");
    if(v2) quitf(_res, "the sum of digits of output must be divided by n");
    return 1;
}
int main(int argc, char * argv[])
{
    setName("checker of baidu-astar2019-digits-sum");
    registerTestlibCmd(argc, argv);
    int T = inf.readInt();
    for(int cs = 1; cs <= T; cs++) {
        n = inf.readInt();
        int ans_res = read_output(ans, _fail);
        int ouf_res = read_output(ouf, _wa);
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

