// Rujia Liu
#include<iostream>
#include<string>
#include<sstream>
#include<cctype>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;

void make_dict(string s, map<string,string>& m, vector<string>& keys) {
  for(int i = 0; i < s.size(); i++) {
    if(!isalpha(s[i]) && !isdigit(s[i])) s[i] = ' ';
  }
  stringstream ss(s);
  string key, value;
  while(ss >> key) {
    ss >> value;
    m[key] = value;
    keys.push_back(key);
  }
}

void print_list(const vector<string> v) {
  for(int i = 0; i < v.size(); i++) {
    if(i != 0) cout << ',';
    cout << v[i];
  }
  cout << '\n';
}

int main() {
  int T;
  cin >> T;
  while(T--) {
    string d1, d2;
    map<string,string> m1, m2;
    vector<string> all, added, removed, changed;
    cin >> d1 >> d2;
    make_dict(d1, m1, all);
    make_dict(d2, m2, all);
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    for(int i = 0; i < all.size(); i++) {
      string key = all[i];
      if(!m1.count(key) && m2.count(key)) added.push_back(key);
      if(m1.count(key) && !m2.count(key)) removed.push_back(key);
      if(m1.count(key) && m2.count(key) && m1[key] != m2[key]) changed.push_back(key);
    }
    int flag = 0;
    if(!added.empty()) { flag = 1; cout << "+"; print_list(added); }
    if(!removed.empty()) { flag = 1; cout << "-"; print_list(removed); }
    if(!changed.empty()) { flag = 1; cout << "*"; print_list(changed); }
    if(!flag) cout << "No changes\n";
    cout << "\n";
  }
  return 0;
}
