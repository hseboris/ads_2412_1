#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 20'001;
vector<vector<int>> g(MAX_SIZE);
vector<bool> visited(MAX_SIZE);
vector<int> tin(MAX_SIZE), up(MAX_SIZE);
set<int> articulation_points;

int timer, m, n;

void dfs(int v, int p = -1) {
  visited[v] = true;
  tin[v] = up[v] = ++timer;
  int children = 0;
  for (int w : g[v]) {
    if (w == p) {
      continue;
    }
    if (!visited[w]) {
      dfs(w, v);
      up[v] = min(up[v], up[w]);
      if (up[w] >= tin[v] && p != -1) {
        articulation_points.insert(v);
      }
      ++children;
    } else {
      up[v] = min(up[v], tin[w]);
    }
  }
  if (p == -1 && children > 1) {
    articulation_points.insert(v);
  }
}

int main() {
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      dfs(i);
    }
  }
  cout << articulation_points.size() << '\n';
  for (int v : articulation_points) {
    cout << v << '\n';
  }
}