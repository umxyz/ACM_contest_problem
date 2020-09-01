// Rujia Liu
#include<cstdio>
#include<cstring>
#include<cassert>
#include<vector>
#include<set>
using namespace std;

const int maxr = 10 + 5;
const int maxc = 10 + 5;
const int maxnr = 8 + 5;
const int maxnc = 8 + 5;

int r, c;
struct State {
  int dep;
  int x, y;    // your position
  int cnt;     // how many coins are eaten
  char maze[maxr][maxc];
  int code() {
    int ret = x*c + y;
    for(int i = 0; i < r; i++) for(int j = 0; j < c; j++) ret = ret*257 + maze[i][j];
    return ret * maxnc + cnt;
  }
  void print() {
    printf("cnt = %d\n", cnt);
    for(int i = 0; i < r; i++) {
      for(int j = 0; j < c; j++)
        printf("%c", (x==i && y==j) ? 'S' : maze[i][j]);
      printf("\n");
    }
  }
};

set<int> vis;

// dfs2: find pushable rocks and eat coins

struct Candidate {
  int x, y; // rock position
  int d; // push direction
};
int vis2[maxr][maxc];
vector<Candidate> candi;

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

void dfs2(State& s, int x, int y) {
  if(s.maze[x][y] == 'C') { s.maze[x][y] = '.'; s.cnt++; }
  if(vis2[x][y]) return;
  vis2[x][y] = 1;
  for(int d = 0; d < 4; d++) {
    int nx = x + dx[d];
    int ny = y + dy[d];
    if(nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
    if(s.maze[nx][ny] == 'O') {
      int nx2 = nx + dx[d];
      int ny2 = ny + dy[d];
      if(nx2 >= 0 && nx2 < r && ny2 >= 0 && ny2 < c && s.maze[nx2][ny2] == '.')
        candi.push_back((Candidate){nx, ny, d});
    }
    if(s.maze[nx][ny] == '.' || s.maze[nx][ny] == 'C') dfs2(s, nx, ny);
  }
}

int best;

void dfs(State& s) {
  if(vis.count(s.code())) return;

  memset(vis2, 0, sizeof(vis2));
  candi.clear();
  dfs2(s, s.x, s.y);

  best = max(best, s.cnt);

  vector<Candidate> candi2(candi); // copy from global candidates

  for(int i = 0; i < candi2.size(); i++) {
    State s2;
    memcpy(&s2, &s, sizeof(s));
    s2.dep++;
    int x = candi2[i].x;
    int y = candi2[i].y;
    int d = candi2[i].d;
    s2.maze[x][y] = '.';
    assert(s2.maze[x+dx[d]][y+dy[d]] == '.');
    s2.maze[x+dx[d]][y+dy[d]] = 'X';
    s2.x = x;
    s2.y = y;
    dfs(s2);
  }
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%d%d", &r, &c);
    State start;
    memset(&start, 0, sizeof(start));
    start.x = -1;
    for(int i = 0; i < r; i++) {
      scanf("%s", start.maze[i]);
      assert(strlen(start.maze[i]) == c);
      for(int j = 0; j < c; j++)
        if(start.maze[i][j] == 'S') {
          start.x = i;
          start.y = j;
          start.maze[i][j] = '.';
        }
    }
    assert(start.x != -1);
    vis.clear();
    best = -1;
    dfs(start);
    printf("%d\n", best);
  }
  return 0;
}
