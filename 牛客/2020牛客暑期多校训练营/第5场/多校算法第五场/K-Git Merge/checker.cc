#include <bits/stdc++.h>
using namespace std;

FILE *in, *out, *ans;


const int SIZE = 4000 * 257, L = 5003, C = 303;
char fin[SIZE], code[SIZE], output[SIZE];
char inl[L][C];
int lcnt, ccnt;
char ansl[L][C];

int ans_cnt = 0;
void read_ans() {
    fread(fin, 1, SIZE, in);
    
    int i = 0;
    while (fin[i]) i++;
    while (i >= 2 && (fin[i - 1] == '\n' && fin[i - 2] == '\n')) {
        i--;
        fin[i] = EOF;
    }
    if (fin[i - 1] != '\n') fin[i++] = '\n';
    ans_cnt = 0;
    for (int k = 0; k < i; k++) {
        if (fin[k] == '\n') {
            ans_cnt++;
        }
    }
    int cur = 0, pos = 0;
    for (int k = 0; k < i; k++) {
        if (fin[k] == '\n') {
            while (pos > 0 && ansl[cur][pos - 1] == ' ') {
                ansl[cur][pos - 1] = 0;
                pos--;
            }
            cur++; pos = 0;
        } else {
            ansl[cur][pos++] = fin[k];
            if (pos == C) {
                exit(1); // ?
            }
        }
    }
}

void check_line_cnt() {    
    int i = 0;
    while (output[i]) i++;
    while (i >= 2 && (output[i - 1] == '\n' && output[i - 2] == '\n')) {
        i--;
        output[i] = EOF;
    }
    if (i == 0) exit(1);
    if (output[i - 1] != '\n') output[i++] = '\n';
    ccnt = 0;
    for (int k = 0; k < i; k++) {
        if (output[k] == '\n') {
            ccnt++;
        }
    }

    i = 0;
    while (code[i]) i++;
    while (i >= 2 && (code[i - 1] == '\n' && code[i - 2] == '\n')) {
        i--;
        code[i] = EOF;
    }
    if (i == 0) exit(1);
    if (code[i - 1] != '\n') code[i++] = '\n';
    lcnt = 0;
    for (int k = 0; k < i; k++) {
        if (code[k] == '\n') {
            lcnt++;
        }
    }
    
    if (lcnt > ccnt) exit(1);
    
    // hopefully, if you fucked std, you nb
    int cur = 0, pos = 0;
    for (int k = 0; k < i; k++) {
        if (code[k] == '\n') {
            while (pos > 0 && inl[cur][pos - 1] == ' ') {
                inl[cur][pos - 1] = 0;
                pos--;
            }
            cur++; pos = 0;
        } else {
            inl[cur][pos++] = code[k];
            if (pos == C) {
                exit(1);
            }
        }
    }
}

bool start_with(const char* s, const char* t) {
    while (*s <= ' ' && *s) s++;
    while (*t) {
        if (*s != *t) return 0;
        s ++, t ++;
    }
    return 1;
}

vector <string> tokenize(char * s) {
    vector <string> ret;
    for (int i = 0; s[i]; ) {
        while (s[i] <= ' ') {
            if (!s[i]) break;
            if (s[i] != '\t' && s[i] != '\n' && s[i] != ' ') {
                exit(1);
            }
            i++;
        }
        if (!s[i]) break;
        string cur = "";
        while (s[i] > ' ') {
            cur += s[i];
            i++;
        }
        ret.push_back(cur);
    }
    return ret;
}

void check_bracket() {
    int state = 0, el = 0;
    for (int i = 0; i < lcnt; i++) {
        if (start_with(inl[i], "#ifdef")) {
            auto x = tokenize(inl[i]);
            if (x.size() != 2 || x[0] != "#ifdef") exit(1);
            if (x[1] == "branch1") {
                if (state != 0) {
                    exit(1);
                }
                state = 1, el = 0;
            } else if (x[1] == "branch2") {
                if (state != 0) {
                    exit(1);
                }
                state = 2, el = 0;
            } 
        } else if (start_with(inl[i], "#else")) {
            auto x = tokenize(inl[i]);
            if (x.size() != 1 || x[0] != "#else") exit(1);
            if (state == 0 || el) {
                exit(1);
            }
            el = 1;
            state = 3 - state;
        } else if (start_with(inl[i], "#endif")) {
            auto x = tokenize(inl[i]);
            if (x.size() != 1 || x[0] != "#endif") exit(1);
            if (state == 0) {
                exit(1);
            }
            state = 0, el = 0;
        }
    }
    if (state) {
        exit(1);
    }
}

string f1, f2, u1, u2;

void get_std() {
    int state = 0;
    for (int i = 0; i < ans_cnt; i++) {
        if (start_with(ansl[i], "<<<<<<< branch1")) {
            state = 1;
        } else if (start_with(ansl[i], "=======")) {
            state = 2;
        } else if (start_with(ansl[i], ">>>>>>> branch2")) {
            state = 0;
        } else {
            switch (state)
            {
            case 1:
                f1 += ansl[i];
                f1 += '\n';
                break;
            case 2:
                f2 += ansl[i];
                f2 += '\n';
                break;
            default:
                f1 += ansl[i];
                f1 += '\n';
                f2 += ansl[i];
                f2 += '\n';
                break;
            }
        }
    }
}

void get_user() {
    int state = 0;
    for (int i = 0; i < lcnt; i++) {
        if (start_with(inl[i], "#ifdef")) {
            auto x = tokenize(inl[i]);
            if (x[1] == "branch1") {
                state = 1;
            } else if (x[1] == "branch2") {
                state = 2;
            } 
        } else if (start_with(inl[i], "#else")) {
            state = 3 - state;
        } else if (start_with(inl[i], "#endif")) {
            state = 0;
        } else {
            switch (state)
            {
            case 1:
                u1 += inl[i];
                u1 += '\n';
                break;
            case 2:
                u2 += inl[i];
                u2 += '\n';
                break;
            default:
                u1 += inl[i];
                u1 += '\n';
                u2 += inl[i];
                u2 += '\n';
                break;
            }
        }
    }
    if (f1 != u1 || f2 != u2) {
        exit(1);
    }
}

int main() {
    in = fopen("input", "r");
    ans = fopen("output", "r");
    out = fopen("user_output", "r");
    read_ans();
    size_t rcnt = fread(code, 1, SIZE, out);
    size_t ocnt = fread(output, 1, SIZE, ans);

    if (rcnt == 0 || rcnt == SIZE) exit(1); // empty or too large
    check_line_cnt();
    check_bracket();
    get_std();
    get_user();
    exit(0);
}