// 669
#include <bits/stdc++.h>
using namespace std;

const int INF = numeric_limits<int>::max();
const int MAX_N = 101;

struct coord {
  int x, y, z;
};

int dx[] = {1, -1, 0, 0, 0, 0};
int dy[] = {0, 0, 1, -1, 0, 0};
int dz[] = {0, 0, 0, 0, 1, -1};

int n, ans = -1;
coord st;
vector<vector<vector<bool>>> g(MAX_N, vector<vector<bool>>(MAX_N, vector<bool>(MAX_N)));
vector<vector<vector<int>>> dist(MAX_N, vector<vector<int>>(MAX_N, vector<int>(MAX_N, INF)));

bool is_valid(int x, int y, int z) {
  return x >= 1 && x <= n && y >= 1 && y <= n && z >= 1 && z <= n;
}

void bfs() {
  queue<coord> q;
  q.push(st);
  dist[st.x][st.y][st.z] = 0;
  while (!q.empty()) {
    coord v = q.front();
    q.pop();
    if (v.x == 1) {
      ans = dist[v.x][v.y][v.z];
      return;
    }
    for (int i = 0; i < 6; ++i) {
      int x = v.x + dx[i];
      int y = v.y + dy[i];
      int z = v.z + dz[i];
      if (is_valid(x, y, z) && g[x][y][z] && dist[x][y][z] > dist[v.x][v.y][v.z] + 1) {
        dist[x][y][z] = dist[v.x][v.y][v.z] + 1;
        q.emplace(x, y, z);
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      string s;
      cin >> s;
      for (int k = 0; k < n; ++k) {
        if (s[k] != '#') {
          g[i][j][k + 1] = true;
        }
        if (s[k] == 'S') {
          st = {i, j, k + 1};
        }
      }
    }
  }
  bfs();
  cout << ans;
}