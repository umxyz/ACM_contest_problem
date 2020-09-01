// Rujia Liu
#include<cstdio>
#include<iostream>
#include<string>
#include<cassert>
using namespace std;

int score1, score2, ans;

const int num[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int s2t(const string& s) {
  int hh, mm, ss;
  sscanf(s.c_str(), "%d:%d:%d", &hh, &mm, &ss);
  assert(hh>=9 && hh<=21 && mm>=0 && mm<=59 && ss>=0 && ss<=59);
  int ans = hh * 3600 + mm * 60 + ss;
  assert(ans>=9*3600 && ans<=21*3600);
  return ans;
}

void accumulate(int score, int dt) {
  char n[99];
  sprintf(n, "%d", score);
  for(int i = 0; i < strlen(n); i++)
    ans += dt * num[n[i] - '0'];
}

int main() {
  int kase = 0, score;
  string s, s2, team;
  while(cin >> s >> s2) {
    score1 = score2 = ans = 0;
    assert(s == "START");
    int last_t = s2t(s2);
    while(cin >> s >> s2) {
      int t = s2t(s2);
      assert(t > last_t);
      accumulate(score1, t - last_t);
      accumulate(score2, t - last_t);
      last_t = t;
      if(s == "END") break;
      assert(s == "SCORE");
      
      cin >> team >> score;
      assert(score>=1 && score<=3);
      if(team == "home") score1 += score;
      else if(team == "guest") score2 += score;
      else assert(0);
    }
    cout << "Case " << ++kase << ": " << ans << "\n";
  }
  return 0;
}
