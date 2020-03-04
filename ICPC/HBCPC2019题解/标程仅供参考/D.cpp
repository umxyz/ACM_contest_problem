#include <bits/stdc++.h>
using namespace std;

set<string> st = {
    "Accepted",      "Wrong Answer",          "Time Limit Exceeded",
    "Compile Error", "Memory Limit Exceeded", "Output Limit Exceeded",
    "Runtime Error", "Presentation Error"};
map<string, int> school;
int n, m, mxname;

struct school {
    string name;
    int pen, num;
    int fa[20];
    bool guo[20];
    bool operator<(const school &rhs) const {
        return num == rhs.num
                   ? (pen == rhs.pen ? name < rhs.name : pen < rhs.pen)
                   : num > rhs.num;
    }
} team[3000];

void deal(string s) {
    stringstream in(s);
    string state, name;
    string tmp;
    int hour, minute;
    char tt;
    in >> hour >> tt >> minute >> tmp;
    int id = tmp[0] - 'A';
    in >> state;
    while (st.find(state) == st.end()) {
        in >> tmp;
        state += " " + tmp;
    }
    in >> name;
    while (in >> tmp) {
        name += " " + tmp;
    }
    if (state[0] == 'C') {
        return;
    }
    if (school.find(name) == school.end()) {
        school[name] = ++m;
        memset(team[m].guo, 0, sizeof(team[m].guo));
        memset(team[m].fa, 0, sizeof(team[m].fa));
        team[m].name = name;
        mxname = max(mxname, static_cast<int>(name.length()));
    }
    int tid = school[name];
    if (team[tid].guo[id]) {
        return;
    }
    if (state[0] == 'A') {
        ++team[tid].num;
        team[tid].guo[id] = 1;
        team[tid].pen += hour * 60 + minute + 20 * team[tid].fa[id];
    } else {
        ++team[tid].fa[id];
    }
}

void write() {

    sort(team + 1, team + 1 + m);
    printf("%4s  %-*s  %6s  %7s", "Rank", mxname, "Who", "Solved", "Penalty");
    for (int i = 0; i < n; i++) {
        char ts[] = "A";
        ts[0] += i;
        printf("  %3s", ts);
    }
    printf("\n");
    int rk = 1;
    for (int i = 1; i <= m; i++) {
        printf("%4d  %*s  %6d  %7d", rk, mxname, team[i].name.c_str(),
               team[i].num, team[i].pen);
        
        for (int j = 0; j < n; j++) {
            string tmp = "";
            if (team[i].guo[j]) {
                tmp += "+";
                if (team[i].fa[j]) {
                    char wa[] = "0";
                    wa[0] += team[i].fa[j];
                    tmp += wa;
                }
            } else if (team[i].fa[j]) {
                tmp += "-";
                char wa[] = "0";
                wa[0] += team[i].fa[j];
                tmp += wa;
            }
            printf("  %3s", tmp.c_str());
        }
        
        printf("\n");
        if (i < m) {
            if (team[i].num != team[i + 1].num || team[i].pen != team[i + 1].pen) {
                rk++;
            }
        }
    }
}
int main() {
    string line;
    getline(cin, line);
    stringstream in(line);
    in >> n;
    while (getline(cin, line)) {
        if (line.compare("GAME OVER!") == 0) {
            write();
            break;
        } else {
            deal(line);
        }
    }
    return 0;
}
