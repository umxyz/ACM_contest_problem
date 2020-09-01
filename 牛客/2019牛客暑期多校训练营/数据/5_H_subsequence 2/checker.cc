#include "testlib.h"

using namespace std;
typedef long long LL;
const int MAX_M = 10;
const int MAX_N = 100000;
int n,m;
string input[10][10];
void read_input() {
    n = inf.readInt();
    m = inf.readInt();
    for(int i = 0; i < m * (m-1) / 2; i++) {
        string c;
        int sz;
        inf.readWordTo(c);
        fprintf(stderr,"%s\n",c.c_str());
        int x = c[0] - 'a';
        int y = c[1] - 'a';
        if(x > y) swap(x,y);
        sz = inf.readInt();
        if(sz) {
            inf.readWordTo(input[x][y]);
        }
    }
}
int read_output(InStream& ufo,TResult _res){
    string s = ufo.readString();
    if(s=="-1")return -1;
    if((int)s.size() != n) quitf(_res, "the output length should be n");
    for(int i = 0; i < m; i++) {
        for(int j = i + 1; j < m; j++) {
            int it=0;
            for(char c: s) {
                if(c == 'a' + i || c == 'a' + j) {
                    if(it == (int)input[i][j].size() || input[i][j][it] != c) {
                        quitf(_res, "the subsequence contain '%c' and '%c' is wrong", 'a' + i, 'a' + j);
                    }
                    it++;
                }
            }
        }
    }
    return 1;
}
int main(int argc, char * argv[])
{
    setName("checker of subsequence2");
    registerTestlibCmd(argc, argv);
    {
        read_input();
        int ans_res = read_output(ans, _fail);
        int ouf_res = read_output(ouf, _wa);
        if(ans_res != ouf_res) {
            if(ans_res == 1)quitf(_wa,"author found solution but user didn't");
            else quitf(_fail, "user found solution but author didn't");
        }
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "Participant output contains extra tokens");
    }
    quitf(_ok, "complete test");
}
